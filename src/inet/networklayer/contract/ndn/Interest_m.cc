//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/contract/ndn/Interest.msg.
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
#include "Interest_m.h"

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

Register_Class(Interest)

Interest::Interest() : ::inet::FieldsChunk()
{
    this->setChunkLength(B(128));

}

Interest::Interest(const Interest& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

Interest::~Interest()
{
}

Interest& Interest::operator=(const Interest& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void Interest::copy(const Interest& other)
{
    this->interestName = other.interestName;
    this->source = other.source;
    this->type = other.type;
    this->hotCount = other.hotCount;
    this->prefixLength = other.prefixLength;
    this->flood = other.flood;
    this->canBePrefix = other.canBePrefix;
    this->MustBeFresh = other.MustBeFresh;
    this->InterestLifeTime = other.InterestLifeTime;
    this->hopLimit = other.hopLimit;
    this->portNumber1 = other.portNumber1;
    this->portNumber2 = other.portNumber2;
    this->MTU = other.MTU;
    this->checksum = other.checksum;
    this->Nonce = other.Nonce;
    this->MAC = other.MAC;
    this->totalLength = other.totalLength;
}

void Interest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->interestName);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->hotCount);
    doParsimPacking(b,this->prefixLength);
    doParsimPacking(b,this->flood);
    doParsimPacking(b,this->canBePrefix);
    doParsimPacking(b,this->MustBeFresh);
    doParsimPacking(b,this->InterestLifeTime);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->portNumber1);
    doParsimPacking(b,this->portNumber2);
    doParsimPacking(b,this->MTU);
    doParsimPacking(b,this->checksum);
    doParsimPacking(b,this->Nonce);
    doParsimPacking(b,this->MAC);
    doParsimPacking(b,this->totalLength);
}

void Interest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->interestName);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->hotCount);
    doParsimUnpacking(b,this->prefixLength);
    doParsimUnpacking(b,this->flood);
    doParsimUnpacking(b,this->canBePrefix);
    doParsimUnpacking(b,this->MustBeFresh);
    doParsimUnpacking(b,this->InterestLifeTime);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->portNumber1);
    doParsimUnpacking(b,this->portNumber2);
    doParsimUnpacking(b,this->MTU);
    doParsimUnpacking(b,this->checksum);
    doParsimUnpacking(b,this->Nonce);
    doParsimUnpacking(b,this->MAC);
    doParsimUnpacking(b,this->totalLength);
}

const iName& Interest::getInterestName() const
{
    return this->interestName;
}

void Interest::setInterestName(const iName& interestName)
{
    handleChange();
    this->interestName = interestName;
}

const iName& Interest::getSource() const
{
    return this->source;
}

void Interest::setSource(const iName& source)
{
    handleChange();
    this->source = source;
}

unsigned char Interest::getType() const
{
    return this->type;
}

void Interest::setType(unsigned char type)
{
    handleChange();
    this->type = type;
}

int Interest::getHotCount() const
{
    return this->hotCount;
}

void Interest::setHotCount(int hotCount)
{
    handleChange();
    this->hotCount = hotCount;
}

short Interest::getPrefixLength() const
{
    return this->prefixLength;
}

void Interest::setPrefixLength(short prefixLength)
{
    handleChange();
    this->prefixLength = prefixLength;
}

bool Interest::getFlood() const
{
    return this->flood;
}

void Interest::setFlood(bool flood)
{
    handleChange();
    this->flood = flood;
}

bool Interest::getCanBePrefix() const
{
    return this->canBePrefix;
}

void Interest::setCanBePrefix(bool canBePrefix)
{
    handleChange();
    this->canBePrefix = canBePrefix;
}

bool Interest::getMustBeFresh() const
{
    return this->MustBeFresh;
}

void Interest::setMustBeFresh(bool MustBeFresh)
{
    handleChange();
    this->MustBeFresh = MustBeFresh;
}

omnetpp::simtime_t Interest::getInterestLifeTime() const
{
    return this->InterestLifeTime;
}

void Interest::setInterestLifeTime(omnetpp::simtime_t InterestLifeTime)
{
    handleChange();
    this->InterestLifeTime = InterestLifeTime;
}

unsigned int Interest::getHopLimit() const
{
    return this->hopLimit;
}

void Interest::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

const Port_t& Interest::getPortNumber1() const
{
    return this->portNumber1;
}

void Interest::setPortNumber1(const Port_t& portNumber1)
{
    handleChange();
    this->portNumber1 = portNumber1;
}

const Port_t& Interest::getPortNumber2() const
{
    return this->portNumber2;
}

void Interest::setPortNumber2(const Port_t& portNumber2)
{
    handleChange();
    this->portNumber2 = portNumber2;
}

uint16_t Interest::getMTU() const
{
    return this->MTU;
}

void Interest::setMTU(uint16_t MTU)
{
    handleChange();
    this->MTU = MTU;
}

uint16_t Interest::getChecksum() const
{
    return this->checksum;
}

void Interest::setChecksum(uint16_t checksum)
{
    handleChange();
    this->checksum = checksum;
}

long Interest::getNonce() const
{
    return this->Nonce;
}

void Interest::setNonce(long Nonce)
{
    handleChange();
    this->Nonce = Nonce;
}

const MacAddress& Interest::getMAC() const
{
    return this->MAC;
}

void Interest::setMAC(const MacAddress& MAC)
{
    handleChange();
    this->MAC = MAC;
}

uint16_t Interest::getTotalLength() const
{
    return this->totalLength;
}

void Interest::setTotalLength(uint16_t totalLength)
{
    handleChange();
    this->totalLength = totalLength;
}

class InterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interestName,
        FIELD_source,
        FIELD_type,
        FIELD_hotCount,
        FIELD_prefixLength,
        FIELD_flood,
        FIELD_canBePrefix,
        FIELD_MustBeFresh,
        FIELD_InterestLifeTime,
        FIELD_hopLimit,
        FIELD_portNumber1,
        FIELD_portNumber2,
        FIELD_MTU,
        FIELD_checksum,
        FIELD_Nonce,
        FIELD_MAC,
        FIELD_totalLength,
    };
  public:
    InterestDescriptor();
    virtual ~InterestDescriptor();

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

Register_ClassDescriptor(InterestDescriptor)

InterestDescriptor::InterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::Interest)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

InterestDescriptor::~InterestDescriptor()
{
    delete[] propertynames;
}

bool InterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Interest *>(obj)!=nullptr;
}

const char **InterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *InterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int InterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 17+basedesc->getFieldCount() : 17;
}

unsigned int InterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_interestName
        0,    // FIELD_source
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_hotCount
        FD_ISEDITABLE,    // FIELD_prefixLength
        FD_ISEDITABLE,    // FIELD_flood
        FD_ISEDITABLE,    // FIELD_canBePrefix
        FD_ISEDITABLE,    // FIELD_MustBeFresh
        0,    // FIELD_InterestLifeTime
        FD_ISEDITABLE,    // FIELD_hopLimit
        0,    // FIELD_portNumber1
        0,    // FIELD_portNumber2
        FD_ISEDITABLE,    // FIELD_MTU
        FD_ISEDITABLE,    // FIELD_checksum
        FD_ISEDITABLE,    // FIELD_Nonce
        0,    // FIELD_MAC
        FD_ISEDITABLE,    // FIELD_totalLength
    };
    return (field >= 0 && field < 17) ? fieldTypeFlags[field] : 0;
}

const char *InterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interestName",
        "source",
        "type",
        "hotCount",
        "prefixLength",
        "flood",
        "canBePrefix",
        "MustBeFresh",
        "InterestLifeTime",
        "hopLimit",
        "portNumber1",
        "portNumber2",
        "MTU",
        "checksum",
        "Nonce",
        "MAC",
        "totalLength",
    };
    return (field >= 0 && field < 17) ? fieldNames[field] : nullptr;
}

int InterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestName") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "source") == 0) return base+1;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+2;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hotCount") == 0) return base+3;
    if (fieldName[0] == 'p' && strcmp(fieldName, "prefixLength") == 0) return base+4;
    if (fieldName[0] == 'f' && strcmp(fieldName, "flood") == 0) return base+5;
    if (fieldName[0] == 'c' && strcmp(fieldName, "canBePrefix") == 0) return base+6;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MustBeFresh") == 0) return base+7;
    if (fieldName[0] == 'I' && strcmp(fieldName, "InterestLifeTime") == 0) return base+8;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+9;
    if (fieldName[0] == 'p' && strcmp(fieldName, "portNumber1") == 0) return base+10;
    if (fieldName[0] == 'p' && strcmp(fieldName, "portNumber2") == 0) return base+11;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MTU") == 0) return base+12;
    if (fieldName[0] == 'c' && strcmp(fieldName, "checksum") == 0) return base+13;
    if (fieldName[0] == 'N' && strcmp(fieldName, "Nonce") == 0) return base+14;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MAC") == 0) return base+15;
    if (fieldName[0] == 't' && strcmp(fieldName, "totalLength") == 0) return base+16;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *InterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_interestName
        "inet::iName",    // FIELD_source
        "unsigned char",    // FIELD_type
        "int",    // FIELD_hotCount
        "short",    // FIELD_prefixLength
        "bool",    // FIELD_flood
        "bool",    // FIELD_canBePrefix
        "bool",    // FIELD_MustBeFresh
        "omnetpp::simtime_t",    // FIELD_InterestLifeTime
        "unsigned int",    // FIELD_hopLimit
        "inet::Port_t",    // FIELD_portNumber1
        "inet::Port_t",    // FIELD_portNumber2
        "uint16_t",    // FIELD_MTU
        "uint16_t",    // FIELD_checksum
        "long",    // FIELD_Nonce
        "inet::MacAddress",    // FIELD_MAC
        "uint16_t",    // FIELD_totalLength
    };
    return (field >= 0 && field < 17) ? fieldTypeStrings[field] : nullptr;
}

const char **InterestDescriptor::getFieldPropertyNames(int field) const
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

const char *InterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int InterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Interest *pp = (Interest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *InterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Interest *pp = (Interest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string InterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Interest *pp = (Interest *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: {std::stringstream out; out << pp->getInterestName(); return out.str();}
        case FIELD_source: {std::stringstream out; out << pp->getSource(); return out.str();}
        case FIELD_type: return ulong2string(pp->getType());
        case FIELD_hotCount: return long2string(pp->getHotCount());
        case FIELD_prefixLength: return long2string(pp->getPrefixLength());
        case FIELD_flood: return bool2string(pp->getFlood());
        case FIELD_canBePrefix: return bool2string(pp->getCanBePrefix());
        case FIELD_MustBeFresh: return bool2string(pp->getMustBeFresh());
        case FIELD_InterestLifeTime: return simtime2string(pp->getInterestLifeTime());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        case FIELD_portNumber1: {std::stringstream out; out << pp->getPortNumber1(); return out.str();}
        case FIELD_portNumber2: {std::stringstream out; out << pp->getPortNumber2(); return out.str();}
        case FIELD_MTU: return ulong2string(pp->getMTU());
        case FIELD_checksum: return ulong2string(pp->getChecksum());
        case FIELD_Nonce: return long2string(pp->getNonce());
        case FIELD_MAC: return pp->getMAC().str();
        case FIELD_totalLength: return ulong2string(pp->getTotalLength());
        default: return "";
    }
}

bool InterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Interest *pp = (Interest *)object; (void)pp;
    switch (field) {
        case FIELD_type: pp->setType(string2ulong(value)); return true;
        case FIELD_hotCount: pp->setHotCount(string2long(value)); return true;
        case FIELD_prefixLength: pp->setPrefixLength(string2long(value)); return true;
        case FIELD_flood: pp->setFlood(string2bool(value)); return true;
        case FIELD_canBePrefix: pp->setCanBePrefix(string2bool(value)); return true;
        case FIELD_MustBeFresh: pp->setMustBeFresh(string2bool(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        case FIELD_MTU: pp->setMTU(string2ulong(value)); return true;
        case FIELD_checksum: pp->setChecksum(string2ulong(value)); return true;
        case FIELD_Nonce: pp->setNonce(string2long(value)); return true;
        case FIELD_totalLength: pp->setTotalLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *InterestDescriptor::getFieldStructName(int field) const
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

void *InterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Interest *pp = (Interest *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: return toVoidPtr(&pp->getInterestName()); break;
        case FIELD_source: return toVoidPtr(&pp->getSource()); break;
        case FIELD_portNumber1: return toVoidPtr(&pp->getPortNumber1()); break;
        case FIELD_portNumber2: return toVoidPtr(&pp->getPortNumber2()); break;
        case FIELD_MAC: return toVoidPtr(&pp->getMAC()); break;
        default: return nullptr;
    }
}

} // namespace inet

