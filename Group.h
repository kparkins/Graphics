#ifndef CUBE_GROUP_H
#define CUBE_GROUP_H

#include <algorithm>
#include <vector>
#include "Node.h"

using std::find;
using std::vector;

class Group : public Node {

public:

    Group();
    ~Group();

    void addChild(NodePtr child);
    void removeChild(NodePtr child);

    void draw(Matrix4 & c) override;

protected:

    vector<NodePtr> m_children;

};

typedef shared_ptr<Group> GroupPtr;

#endif