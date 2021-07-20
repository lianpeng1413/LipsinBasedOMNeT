//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/ndn/PIT/pitEntry.msg.
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
#include "pitEntry_m.h"

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

Register_Class(pitEntry)

pitEntry::pitEntry() : ::omnetpp::cObject()
{
}

pitEntry::pitEntry(const pitEntry& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

pitEntry::~pitEntry()
{
}

pitEntry& pitEntry::operator=(const pitEntry& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void pitEntry::copy(const pitEntry& other)
{
    this->nidName = other.nidName;
    this->TTL = other.TTL;
    this->mac = other.mac;
    this->interfaceId = other.interfaceId;
    this->Nonce = other.Nonce;
    this->served = other.served;
    this->isConsumer_ = other.isConsumer_;
}

void pitEntry::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->nidName);
    doParsimPacking(b,this->TTL);
    doParsimPacking(b,this->mac);
    doParsimPacking(b,this->interfaceId);
    doParsimPacking(b,this->Nonce);
    doParsimPacking(b,this->served);
    doParsimPacking(b,this->isConsumer_);
}

void pitEntry::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->nidName);
    doParsimUnpacking(b,this->TTL);
    doParsimUnpacking(b,this->mac);
    doParsimUnpacking(b,this->interfaceId);
    doParsimUnpacking(b,this->Nonce);
    doParsimUnpacking(b,this->served);
    doParsimUnpacking(b,this->isConsumer_);
}

const inet::iName& pitEntry::getNidName() const
{
    return this->nidName;
}

void pitEntry::setNidName(const inet::iName& nidName)
{
    this->nidName = nidName;
}

omnetpp::simtime_t pitEntry::getTTL() const
{
    return this->TTL;
}

void pitEntry::setTTL(omnetpp::simtime_t TTL)
{
    this->TTL = TTL;
}

const MacAddress& pitEntry::getMac() const
{
    return this->mac;
}

void pitEntry::setMac(const MacAddress& mac)
{
    this->mac = mac;
}

int pitEntry::getInterfaceId() const
{
    return this->interfaceId;
}

void pitEntry::setInterfaceId(int interfaceId)
{
    this->interfaceId = interfaceId;
}

long pitEntry::getNonce() const
{
    return this->Nonce;
}

void pitEntry::setNonce(long Nonce)
{
    this->Nonce = Nonce;
}

bool pitEntry::getServed() const
{
    return this->served;
}

void pitEntry::setServed(bool served)
{
    this->served = served;
}

bool pitEntry::isConsumer() const
{
    return this->isConsumer_;
}

void pitEntry::setIsConsumer(bool isConsumer)
{
    this->isConsumer_ = isConsumer;
}

class pitEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_nidName,
        FIELD_TTL,
        FIELD_mac,
        FIELD_interfaceId,
        FIELD_Nonce,
        FIELD_served,
        FIELD_isConsumer,
    };
  public:
    pitEntryDescriptor();
    virtual ~pitEntryDescriptor();

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

Register_ClassDescriptor(pitEntryDescriptor)

pitEntryDescriptor::pitEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::pitEntry)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

pitEntryDescriptor::~pitEntryDescriptor()
{
    delete[] propertynames;
}

bool pitEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<pitEntry *>(obj)!=nullptr;
}

const char **pitEntryDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *pitEntryDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int pitEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int pitEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_nidName
        0,    // FIELD_TTL
        0,    // FIELD_mac
        FD_ISEDITABLE,    // FIELD_interfaceId
        FD_ISEDITABLE,    // FIELD_Nonce
        FD_ISEDITABLE,    // FIELD_served
        FD_ISEDITABLE,    // FIELD_isConsumer
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *pitEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nidName",
        "TTL",
        "mac",
        "interfaceId",
        "Nonce",
        "served",
        "isConsumer",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int pitEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nidName") == 0) return base+0;
    if (fieldName[0] == 'T' && strcmp(fieldName, "TTL") == 0) return base+1;
    if (fieldName[0] == 'm' && strcmp(fieldName, "mac") == 0) return base+2;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interfaceId") == 0) return base+3;
    if (fieldName[0] == 'N' && strcmp(fieldName, "Nonce") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "served") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "isConsumer") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *pitEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_nidName
        "omnetpp::simtime_t",    // FIELD_TTL
        "inet::MacAddress",    // FIELD_mac
        "int",    // FIELD_interfaceId
        "long",    // FIELD_Nonce
        "bool",    // FIELD_served
        "bool",    // FIELD_isConsumer
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **pitEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *pitEntryDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int pitEntryDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    pitEntry *pp = (pitEntry *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *pitEntryDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    pitEntry *pp = (pitEntry *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string pitEntryDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    pitEntry *pp = (pitEntry *)object; (void)pp;
    switch (field) {
        case FIELD_nidName: {std::stringstream out; out << pp->getNidName(); return out.str();}
        case FIELD_TTL: return simtime2string(pp->getTTL());
        case FIELD_mac: return pp->getMac().str();
        case FIELD_interfaceId: return long2string(pp->getInterfaceId());
        case FIELD_Nonce: return long2string(pp->getNonce());
        case FIELD_served: return bool2string(pp->getServed());
        case FIELD_isConsumer: return bool2string(pp->isConsumer());
        default: return "";
    }
}

bool pitEntryDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    pitEntry *pp = (pitEntry *)object; (void)pp;
    switch (field) {
        case FIELD_interfaceId: pp->setInterfaceId(string2long(value)); return true;
        case FIELD_Nonce: pp->setNonce(string2long(value)); return true;
        case FIELD_served: pp->setServed(string2bool(value)); return true;
        case FIELD_isConsumer: pp->setIsConsumer(string2bool(value)); return true;
        default: return false;
    }
}

const char *pitEntryDescriptor::getFieldStructName(int field) const
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

void *pitEntryDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    pitEntry *pp = (pitEntry *)object; (void)pp;
    switch (field) {
        case FIELD_nidName: return toVoidPtr(&pp->getNidName()); break;
        case FIELD_mac: return toVoidPtr(&pp->getMac()); break;
        default: return nullptr;
    }
}

} // namespace inet

