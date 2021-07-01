//
// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/common/INETUtils.h"
#include "inet/networklayer/lipsin/LipsinHeader_m.h"

namespace inet{
Register_Class(LipsinHeader);

bool LipsinHeader::preRouteContains(int linkID)
{
    if(!init) initialize();
    return this->preRoute->contains(linkID);
}

void LipsinHeader::addLinkToPreRoute(int linkID)
{
    if(!init) initialize();
    this->preRoute->insert(linkID);
}

bool LipsinHeader::hadRouteContains(int linkID)
{
    if(!init) initialize();
    return this->hadRoute->contains(linkID);
}

void LipsinHeader::addLinkToHadRoute(int linkID)
{
    if(!init) initialize();
    this->hadRoute->insert(linkID);
}
}
