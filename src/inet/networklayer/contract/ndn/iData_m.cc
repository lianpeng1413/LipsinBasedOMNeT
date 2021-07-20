//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/contract/ndn/iData.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include "iData_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace {
template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)(static_cast<const omnetpp::cObject *>(t));
}

template <class T> inline
typename std::enable_if<std::is_polymorphic<T>::value && !std::is_base_of<omnetpp::cObject,T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)dynamic_cast<const void *>(t);
}

template <class T> inline
typename std::enable_if<!std::is_polymorphic<T>::value, void *>::type
toVoidPtr(T* t)
{
    return (void *)static_cast<const void *>(t);
}

}

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(iData)

iData::iData() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(128));

}

iData::iData(const iData& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

iData::~iData()
{
}

iData& iData::operator=(const iData& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void iData::copy(const iData& other)
{
    this->interestName = other.interestName;
    this->type = other.type;
    this->hotCount = other.hotCount;
    this->timeToLive = other.timeToLive;
    this->checksum = other.checksum;
    this->moreFragments = other.moreFragments;
    this->portNumber1 = other.portNumber1;
    this->portNumber2 = other.portNumber2;
    this->MAC = other.MAC;
    this->offset = other.offset;
    this->HeaderLength = other.HeaderLength;
    this->lastHop = other.lastHop;
    this->MTU = other.MTU;
    this->comeFromSource = other.comeFromSource;
    this->routeLifetime = other.routeLifetime;
    this->routeMetric = other.routeMetric;
    this->totalLength = other.totalLength;
}

void iData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->interestName);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->hotCount);
    doParsimPacking(b,this->timeToLive);
    doParsimPacking(b,this->checksum);
    doParsimPacking(b,this->moreFragments);
    doParsimPacking(b,this->portNumber1);
    doParsimPacking(b,this->portNumber2);
    doParsimPacking(b,this->MAC);
    doParsimPacking(b,this->offset);
    doParsimPacking(b,this->HeaderLength);
    doParsimPacking(b,this->lastHop);
    doParsimPacking(b,this->MTU);
    doParsimPacking(b,this->comeFromSource);
    doParsimPacking(b,this->routeLifetime);
    doParsimPacking(b,this->routeMetric);
    doParsimPacking(b,this->totalLength);
}

void iData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->interestName);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->hotCount);
    doParsimUnpacking(b,this->timeToLive);
    doParsimUnpacking(b,this->checksum);
    doParsimUnpacking(b,this->moreFragments);
    doParsimUnpacking(b,this->portNumber1);
    doParsimUnpacking(b,this->portNumber2);
    doParsimUnpacking(b,this->MAC);
    doParsimUnpacking(b,this->offset);
    doParsimUnpacking(b,this->HeaderLength);
    doParsimUnpacking(b,this->lastHop);
    doParsimUnpacking(b,this->MTU);
    doParsimUnpacking(b,this->comeFromSource);
    doParsimUnpacking(b,this->routeLifetime);
    doParsimUnpacking(b,this->routeMetric);
    doParsimUnpacking(b,this->totalLength);
}

const iName& iData::getInterestName() const
{
    return this->interestName;
}

void iData::setInterestName(const iName& interestName)
{
    handleChange();
    this->interestName = interestName;
}

unsigned char iData::getType() const
{
    return this->type;
}

void iData::setType(unsigned char type)
{
    handleChange();
    this->type = type;
}

int iData::getHotCount() const
{
    return this->hotCount;
}

void iData::setHotCount(int hotCount)
{
    handleChange();
    this->hotCount = hotCount;
}

int iData::getTimeToLive() const
{
    return this->timeToLive;
}

void iData::setTimeToLive(int timeToLive)
{
    handleChange();
    this->timeToLive = timeToLive;
}

uint16_t iData::getChecksum() const
{
    return this->checksum;
}

void iData::setChecksum(uint16_t checksum)
{
    handleChange();
    this->checksum = checksum;
}

bool iData::getMoreFragments() const
{
    return this->moreFragments;
}

void iData::setMoreFragments(bool moreFragments)
{
    handleChange();
    this->moreFragments = moreFragments;
}

const Port_t& iData::getPortNumber1() const
{
    return this->portNumber1;
}

void iData::setPortNumber1(const Port_t& portNumber1)
{
    handleChange();
    this->portNumber1 = portNumber1;
}

const Port_t& iData::getPortNumber2() const
{
    return this->portNumber2;
}

void iData::setPortNumber2(const Port_t& portNumber2)
{
    handleChange();
    this->portNumber2 = portNumber2;
}

const MacAddress& iData::getMAC() const
{
    return this->MAC;
}

void iData::setMAC(const MacAddress& MAC)
{
    handleChange();
    this->MAC = MAC;
}

uint32_t iData::getOffset() const
{
    return this->offset;
}

void iData::setOffset(uint32_t offset)
{
    handleChange();
    this->offset = offset;
}

B iData::getHeaderLength() const
{
    return this->HeaderLength;
}

void iData::setHeaderLength(B HeaderLength)
{
    handleChange();
    this->HeaderLength = HeaderLength;
}

const iName& iData::getLastHop() const
{
    return this->lastHop;
}

void iData::setLastHop(const iName& lastHop)
{
    handleChange();
    this->lastHop = lastHop;
}

uint16_t iData::getMTU() const
{
    return this->MTU;
}

void iData::setMTU(uint16_t MTU)
{
    handleChange();
    this->MTU = MTU;
}

bool iData::getComeFromSource() const
{
    return this->comeFromSource;
}

void iData::setComeFromSource(bool comeFromSource)
{
    handleChange();
    this->comeFromSource = comeFromSource;
}

omnetpp::simtime_t iData::getRouteLifetime() const
{
    return this->routeLifetime;
}

void iData::setRouteLifetime(omnetpp::simtime_t routeLifetime)
{
    handleChange();
    this->routeLifetime = routeLifetime;
}

int iData::getRouteMetric() const
{
    return this->routeMetric;
}

void iData::setRouteMetric(int routeMetric)
{
    handleChange();
    this->routeMetric = routeMetric;
}

B iData::getTotalLength() const
{
    return this->totalLength;
}

void iData::setTotalLength(B totalLength)
{
    handleChange();
    this->totalLength = totalLength;
}

class iDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interestName,
        FIELD_type,
        FIELD_hotCount,
        FIELD_timeToLive,
        FIELD_checksum,
        FIELD_moreFragments,
        FIELD_portNumber1,
        FIELD_portNumber2,
        FIELD_MAC,
        FIELD_offset,
        FIELD_HeaderLength,
        FIELD_lastHop,
        FIELD_MTU,
        FIELD_comeFromSource,
        FIELD_routeLifetime,
        FIELD_routeMetric,
        FIELD_totalLength,
    };
  public:
    iDataDescriptor();
    virtual ~iDataDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(iDataDescriptor)

iDataDescriptor::iDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::iData)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

iDataDescriptor::~iDataDescriptor()
{
    delete[] propertynames;
}

bool iDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<iData *>(obj)!=nullptr;
}

const char **iDataDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *iDataDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int iDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 17+basedesc->getFieldCount() : 17;
}

unsigned int iDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_interestName
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_hotCount
        FD_ISEDITABLE,    // FIELD_timeToLive
        FD_ISEDITABLE,    // FIELD_checksum
        FD_ISEDITABLE,    // FIELD_moreFragments
        0,    // FIELD_portNumber1
        0,    // FIELD_portNumber2
        0,    // FIELD_MAC
        FD_ISEDITABLE,    // FIELD_offset
        FD_ISEDITABLE,    // FIELD_HeaderLength
        0,    // FIELD_lastHop
        FD_ISEDITABLE,    // FIELD_MTU
        FD_ISEDITABLE,    // FIELD_comeFromSource
        0,    // FIELD_routeLifetime
        FD_ISEDITABLE,    // FIELD_routeMetric
        FD_ISEDITABLE,    // FIELD_totalLength
    };
    return (field >= 0 && field < 17) ? fieldTypeFlags[field] : 0;
}

const char *iDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interestName",
        "type",
        "hotCount",
        "timeToLive",
        "checksum",
        "moreFragments",
        "portNumber1",
        "portNumber2",
        "MAC",
        "offset",
        "HeaderLength",
        "lastHop",
        "MTU",
        "comeFromSource",
        "routeLifetime",
        "routeMetric",
        "totalLength",
    };
    return (field >= 0 && field < 17) ? fieldNames[field] : nullptr;
}

int iDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestName") == 0) return base+0;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hotCount") == 0) return base+2;
    if (fieldName[0] == 't' && strcmp(fieldName, "timeToLive") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "checksum") == 0) return base+4;
    if (fieldName[0] == 'm' && strcmp(fieldName, "moreFragments") == 0) return base+5;
    if (fieldName[0] == 'p' && strcmp(fieldName, "portNumber1") == 0) return base+6;
    if (fieldName[0] == 'p' && strcmp(fieldName, "portNumber2") == 0) return base+7;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MAC") == 0) return base+8;
    if (fieldName[0] == 'o' && strcmp(fieldName, "offset") == 0) return base+9;
    if (fieldName[0] == 'H' && strcmp(fieldName, "HeaderLength") == 0) return base+10;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lastHop") == 0) return base+11;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MTU") == 0) return base+12;
    if (fieldName[0] == 'c' && strcmp(fieldName, "comeFromSource") == 0) return base+13;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routeLifetime") == 0) return base+14;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routeMetric") == 0) return base+15;
    if (fieldName[0] == 't' && strcmp(fieldName, "totalLength") == 0) return base+16;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *iDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_interestName
        "unsigned char",    // FIELD_type
        "int",    // FIELD_hotCount
        "int",    // FIELD_timeToLive
        "uint16_t",    // FIELD_checksum
        "bool",    // FIELD_moreFragments
        "inet::Port_t",    // FIELD_portNumber1
        "inet::Port_t",    // FIELD_portNumber2
        "inet::MacAddress",    // FIELD_MAC
        "uint32_t",    // FIELD_offset
        "inet::B",    // FIELD_HeaderLength
        "inet::iName",    // FIELD_lastHop
        "uint16_t",    // FIELD_MTU
        "bool",    // FIELD_comeFromSource
        "omnetpp::simtime_t",    // FIELD_routeLifetime
        "int",    // FIELD_routeMetric
        "inet::B",    // FIELD_totalLength
    };
    return (field >= 0 && field < 17) ? fieldTypeStrings[field] : nullptr;
}

const char **iDataDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *iDataDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int iDataDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    iData *pp = (iData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *iDataDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    iData *pp = (iData *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string iDataDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    iData *pp = (iData *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: {std::stringstream out; out << pp->getInterestName(); return out.str();}
        case FIELD_type: return ulong2string(pp->getType());
        case FIELD_hotCount: return long2string(pp->getHotCount());
        case FIELD_timeToLive: return long2string(pp->getTimeToLive());
        case FIELD_checksum: return ulong2string(pp->getChecksum());
        case FIELD_moreFragments: return bool2string(pp->getMoreFragments());
        case FIELD_portNumber1: {std::stringstream out; out << pp->getPortNumber1(); return out.str();}
        case FIELD_portNumber2: {std::stringstream out; out << pp->getPortNumber2(); return out.str();}
        case FIELD_MAC: return pp->getMAC().str();
        case FIELD_offset: return ulong2string(pp->getOffset());
        case FIELD_HeaderLength: return unit2string(pp->getHeaderLength());
        case FIELD_lastHop: {std::stringstream out; out << pp->getLastHop(); return out.str();}
        case FIELD_MTU: return ulong2string(pp->getMTU());
        case FIELD_comeFromSource: return bool2string(pp->getComeFromSource());
        case FIELD_routeLifetime: return simtime2string(pp->getRouteLifetime());
        case FIELD_routeMetric: return long2string(pp->getRouteMetric());
        case FIELD_totalLength: return unit2string(pp->getTotalLength());
        default: return "";
    }
}

bool iDataDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    iData *pp = (iData *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        case FIELD_hotCount: pp->setHotCount(string2long(value)); return true;
        case FIELD_timeToLive: pp->setTimeToLive(string2long(value)); return true;
        case FIELD_checksum: pp->setChecksum(string2ulong(value)); return true;
        case FIELD_moreFragments: pp->setMoreFragments(string2bool(value)); return true;
        case FIELD_offset: pp->setOffset(string2ulong(value)); return true;
        case FIELD_HeaderLength: pp->setHeaderLength(B(string2long(value))); return true;
        case FIELD_MTU: pp->setMTU(string2ulong(value)); return true;
        case FIELD_comeFromSource: pp->setComeFromSource(string2bool(value)); return true;
        case FIELD_routeMetric: pp->setRouteMetric(string2long(value)); return true;
        case FIELD_totalLength: pp->setTotalLength(B(string2long(value))); return true;
        default: return false;
    }
}

const char *iDataDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *iDataDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    iData *pp = (iData *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: return toVoidPtr(&pp->getInterestName()); break;
        case FIELD_portNumber1: return toVoidPtr(&pp->getPortNumber1()); break;
        case FIELD_portNumber2: return toVoidPtr(&pp->getPortNumber2()); break;
        case FIELD_MAC: return toVoidPtr(&pp->getMAC()); break;
        case FIELD_lastHop: return toVoidPtr(&pp->getLastHop()); break;
        default: return nullptr;
    }
}

} // namespace inet

