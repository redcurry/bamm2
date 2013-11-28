#ifndef EVENT_H
#define EVENT_H

class Node;


class Event
{
  public:

    Event(const Node* node, double absoluteTime);

    const Node* node() const;
    void setNode(const Node* node);

    double absoluteTime() const;
    void setAbsoluteTime(double time);

  private:

    const Node* _node;
    double _absoluteTime;
};


inline const Node* Event::node() const
{
  return _node;
}


inline void Event::setNode(const Node* node)
{
  _node = node;
}


inline double Event::absoluteTime() const
{
  return _absoluteTime;
}


inline void Event::setAbsoluteTime(double time)
{
  _absoluteTime = time;
}


#endif
