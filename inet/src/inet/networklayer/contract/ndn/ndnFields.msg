//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//namespace inet;

import inet.common.INETDefs;

cplusplus {{

    #include <vector>
    #include <list>

    #include "inet/networklayer/contract/ndn/iName.h"
    using Port_t = unsigned;
//    typedef std::list<inet::iName> NIDS;
//    typedef std::vector<inet::iName> paths; // nodes name set
}}

namespace inet;

enum TYPE
{
    INTEREST=1;
    DATA=2;
};

//class paths
//{
//    @existingClass;
//}
//
//class NIDS
//{
//    @existingClass;
//}

class iName
{
    @existingClass;
    @opaque;
//    @toString(.str());
}

class Port_t
{
    @existingClass;
    @opaque;
}