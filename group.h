#ifndef GFX_GROUP_H
#define GFX_GROUP_H

#include <algorithm>
#include <vector>

#include "node.h"

using std::find;
using std::vector;

namespace gfx {
    class group : public node {

    public:

        group();
        virtual ~group();

        void add(node_ptr child);
        void remove(node_ptr child);

        void draw(mat4 &c) override;

    protected:

        vector<node_ptr> m_children;

    };

    typedef shared_ptr<group> group_ptr;
}

#endif