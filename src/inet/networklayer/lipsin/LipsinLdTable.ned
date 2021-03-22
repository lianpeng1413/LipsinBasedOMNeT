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

package inet.networklayer.lipsin;

import inet.networklayer.contract.IRoutingTable;
//
// TODO auto-generated type
//
simple LipsinLdTable like IRoutingTable
{
    parameters:
        string interfaceTableModule;
        bool forwarding = default(true);
        bool multicastForwarding = default(false);
        string tableName;
        @class(::inet::LipsinLdTable);
        @display("i=block/table");
        @signal[interfaceCreated](type=inet::InterfaceEntry);
        @signal[interfaceDeleted](type=inet::InterfaceEntry);
}

