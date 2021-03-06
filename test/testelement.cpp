/*
 * Copyright (C) 2017~2017 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */

#include "fcitx-utils/element.h"
#include "fcitx-utils/log.h"

namespace test {

class Element : public fcitx::Element {
public:
    using fcitx::Element::addParent;
    using fcitx::Element::removeParent;
    using fcitx::Element::addChild;
    using fcitx::Element::removeChild;
    using fcitx::Element::insertParent;
    using fcitx::Element::insertChild;
    using fcitx::Element::parents;
    using fcitx::Element::childs;
};
}

int main() {
    using test::Element;
    {
        Element e, e2;
        e.addParent(&e2);
        FCITX_ASSERT(e.parents().size() == 1);
        FCITX_ASSERT(e.childs().size() == 0);
        FCITX_ASSERT(e2.parents().size() == 0);
        FCITX_ASSERT(e2.childs().size() == 1);
    }
    {
        Element e, e2;
        e.addParent(&e2);
        e2.addParent(&e);
        FCITX_ASSERT(e.parents().size() == 1);
        FCITX_ASSERT(e.childs().size() == 1);
        FCITX_ASSERT(e2.parents().size() == 1);
        FCITX_ASSERT(e2.childs().size() == 1);
    }
    {
        Element e, *e2 = new Element;
        e.addParent(e2);
        FCITX_ASSERT(e.parents().size() == 1);
        FCITX_ASSERT(e.childs().size() == 0);
        FCITX_ASSERT(e2->parents().size() == 0);
        FCITX_ASSERT(e2->childs().size() == 1);
        delete e2;

        FCITX_ASSERT(e.parents().size() == 0);
        FCITX_ASSERT(e.childs().size() == 0);
    }
    {
        Element e, e2, e3;
        e.addChild(&e2);
        FCITX_ASSERT(e.childs().front() == &e2);
        e.addChild(&e3);
        FCITX_ASSERT(e.childs().front() == &e2);
        FCITX_ASSERT(e.childs().back() == &e3);
        e.insertChild(&e2, &e3);
        // e3 is in, this is no op.
        FCITX_ASSERT(e.childs().front() == &e2);
        FCITX_ASSERT(e.childs().back() == &e3);
        FCITX_ASSERT(e.childs().size() == 2);
        e.removeChild(&e3);
        e.insertChild(&e2, &e3);
        FCITX_ASSERT(e.childs().front() == &e3);
        FCITX_ASSERT(e.childs().back() == &e2);
        FCITX_ASSERT(e.childs().size() == 2);
    }
    return 0;
}
