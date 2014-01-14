#include "SpExModel.h"


double SpExModel::specificLogLikelihood() const
{
    NodeConstIterator beginIt = _tree.beginPostOrderTraversal();
    NodeConstIterator endIt = _tree.beginPostOrderTraversal();

    for (NodeConstIterator it = beginIt; it != endIt; ++it) {
        const Node* node = *it;

        double branchSpeciationProb = calculateBranchSpeciationProb();
        double branchExtinctionProb = calculateBranchExtinctionProb();

        _speciationStack.push(branchSpeciationProb);
        _extinctionStack.push(branchExtinctionProb);

        if (node->isBranchNode()) {
            double branchSpeciationProb1 = _speciationStack.top();
            double branchSpeciationProb2 = _speciationStack.top();

            double branchExtinctionProb1 = _extinctionStack.top();
            double branchExtinctionProb2 = _extinctionStack.top();

            _speciationStack.pop();
            _speciationStack.pop();

            _extinctionStack.pop();
            _extinctionStack.pop();

            double lambda = calculateInstantaneousLambda();

            branchSpeciationProb *=
                lambda * branchSpeciationProb1 * branchSpeciationProb2;

            _speciationStack.push(branchSpeciationProb);
        }
    }
}


void SpExModel::calculateBranchSpeciationAndExtinctionProb()
{
    // TODO: Should be a member variable
    double segmentSize = 1.0;

    double branchSpeciationProb = 0.0;
    double branchExtinctionProb = 0.0;

    double nodeTime = node->pathLengthToRoot();
    double parentNodeTime = node->parentNode()->pathLengthToRoot();

    double segmentStartTime = nodeTime - segmentSize;
    double segmentEndTime = nodeTime;

    // Stay within branch
    while (segmentEndTime > parentNodeTime) {
        if (segmentStartTime < parentNodeTime) {
            segmentStartTime = parentNodeTime;
        }

        // Length of time for this segment
        double deltaT = segmentEndTime - segmentStartTime;

        // Mean lambda and mu for this segment
        double lambda = calculateSegmentLambda
            (segmentStartTime, segmentEndTime);
        double mu = calculateSegmentMu
            (segmentStartTime, segmentEndTime);

        // Speciation and extinction probabilities for this segment
        double segmentSpeciationProb = calculateSegmentSpeciationProb
            (deltaT, lambda, mu, speciationProbInit, extinctionProbInit);
        double segmentExtinctionProb = calculateSegmentExtinctionProb
            (deltaT, lambda, mu, extinctionProbInit);

        // Accumulate speciation and extinction probabilities
        branchSpeciationProb += segmentSpeciationProb;
        branchExtinctionProb += segmentExtinctionProb;

        // Previous probabilities become the initial for next segment
        speciationProbInit = segmentSpeciationProb;
        extinctionProbInit = segmentExtinctionProb;

        // Move one segment back in time
        segmentStartTime -= segmentSize;
        segmentEndTime -= segmentSize;
    }
}

double SpExModel::calculateSegmentLambda()
{
    const SpExEvent* event = findMostRecentEvent(node, endTime);
    double eventTime  = event->absoluteTime();
    double lambdaInit = event->lambdaInit();
    double lambdaRate = event->lambdaRate();

    // Calculate times relative to event absolute time
    double relativeEndTime = endTime - eventTime;

    double lambdaSum = 0.0;
    while (eventTime > startTime) {
        lambdaSum += calculateDefiniteIntegralOfExponential
            (lambdaInit, lambdaRate, 0.0, relativeEndTime);

        oldEventTime = eventTime;

        event = static_cast<SpExEvent*>(findMostRecentEvent(node, eventTime));
        eventTime  = event->absoluteTime();
        lambdaInit = event->lambdaInit();
        lambdaRate = event->lambdaRate();

        relativeEndTime = oldEventTime - eventTime;
    }

    double relativeStartTime = startTime - eventTime;
    lambdaSum += calculateDefiniteIntegralOfExponential
        (lambdaInit, lambdaRate, relativeStartTime, relativeEndTime);

    return (1 / (endTime - startTime)) * lambdaSum;
}


SpExEvent* SpExEvent::findMostRecentEvent(const Node* node, double time) const
{
    // Find event occuring BEFORE time (i.e., excluding event at time time)
}


double SpExModel::calculateMeanExponential
    (double lambdaInit, double lambdaRate, double t1, double t2)
{
    // Equation for the mean of the exponential function
    //
    //   lambda(t) = lambdaInit * e^(lambdaRate * t)
    //
    // is
    //
    //   lambdaInit   e^(lambdaRate*t2) - e^(lambdaRate*t1)
    //   ---------- X -------------------------------------
    //   lambdaRate                  t2 - t1

    if (lambdaRate > 0) {
        double deltaT = t2 - t1;
        double constant = lambdaInit / (lambdaRate * deltaT);
        double expr = std::exp(lambdaRate * t2) - std::exp(lambdaRate * t1);
        return constant * expr;
    } else {
        return lambdaInit;
    }
}


double SpExModel::calculateBranchIntervalSpeciationProb
    (deltaT, lambda, mu, speciationProbInit, extinctionProbInit)
{
    // Equation (from Rabosky 2013):
    //
    //                  e^[(mu-lambda)*dt]*D0*(lambda-mu)^2
    // D(t) = --------------------------------------------------------
    //        [lambda-(lambda*E0)+e^[(mu-lambda)*dt]*(lambda*E0-mu)]^2
    //
    // where D0 is the initial speciation probability and
    // E0 is the initial extinction probability

    double muMinusLambda = mu - lambda;
    double lambdaMinusMu = -muMinusLambda;
    double expMuMinusLambdaTimesDeltaT = std::exp(muMinusLambda * deltaT);
    double lambdaTimesExtinctionProbInit = lambda * extinctionProbInit;

    double numerator = (expMuMinusLambdaTimesDeltaT * speciationProbInit *
        sqr(lambdaMinusMu));

    double denominator = sqr(lambda - lambdaTimesExtinctionProbInit +
        expMuMinusLambdaTimesDeltaT * (lambdaTimesExtinctionProbInit - mu));

    return numerator / denominator;
}


double SpExModel::calculateBranchIntervalExtinctionProb
    (deltaT, lambda, mu, extinctionProbInit)
{
    // Equation (from Rabosky 2013):
    //
    //                         (1-E0)(lambda-mu)
    // E(t) = 1 - -----------------------------------------------
    //            (1-E0)*lambda-e^[(mu-lambda)*dt]*(mu-lambda*E0)
    //
    // where D0 is the initial speciation probability and
    // E0 is the initial extinction probability

    double oneMinusExtinctionProbInit = 1 - extinctionProbInit;
    double muMinusLambda = mu - lambda;
    double lambdaMinusMu = -muMinusLambda;
    double expMuMinusLambdaTimesDeltaT = std::exp(muMinusLambda * deltaT);

    double numerator = oneMinusExtinctionProbInit * lambdaMinusMu;

    double denominator = oneMinusExtinctionProbInit * lambda -
        expMuMinusLambdaTimesDeltaT * (mu - lambda * extinctionProbInit);

    return numerator / denominator;
}


double SpExModel::sqr(double x) const
{
    return x * x;
}
