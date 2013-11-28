#include "ModelProposal.h"
#include <cmath>
#include <algorithm>


double ModelProposal::acceptanceRatio() const
{
  double logRatio = logPriorRatio() + logLikelihoodRatio() + logProposalRatio();
  return std::min(1.0, std::exp(logRatio));
}


double ModelProposal::logPriorRatio() const
{
  return 0.0;
}


double ModelProposal::logLikelihoodRatio() const
{
  return 0.0;
}


double ModelProposal::logProposalRatio() const
{
  return 0.0;
}
