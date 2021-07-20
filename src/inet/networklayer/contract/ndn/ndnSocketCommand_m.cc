//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/contract/ndn/ndnSocketCommand.msg.
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
#include "ndnSocketCommand_m.h"

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

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::ndnCommandCode");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::ndnCommandCode"));
    e->insert(NDN_C_BIND, "NDN_C_BIND");
    e->insert(NDN_C_SEND_INTEREST, "NDN_C_SEND_INTEREST");
    e->insert(NDN_C_CLOSE, "NDN_C_CLOSE");
    e->insert(NDN_C_DESTROY, "NDN_C_DESTROY");
    e->insert(NDN_C_CACHE_DATA, "NDN_C_CACHE_DATA");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::ndnStatusInd");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::ndnStatusInd"));
    e->insert(NDN_I_DATA, "NDN_I_DATA");
    e->insert(NDN_I_SOCKET_CLOSED, "NDN_I_SOCKET_CLOSED");
)

Register_Class(ndnSocketCommandBase)

ndnSocketCommandBase::ndnSocketCommandBase() : ::omnetpp::cObject()
{
}

ndnSocketCommandBase::ndnSocketCommandBase(const ndnSocketCommandBase& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

ndnSocketCommandBase::~ndnSocketCommandBase()
{
}

ndnSocketCommandBase& ndnSocketCommandBase::operator=(const ndnSocketCommandBase& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketCommandBase::copy(const ndnSocketCommandBase& other)
{
}

void ndnSocketCommandBase::parsimPack(omnetpp::cCommBuffer *b) const
{
}

void ndnSocketCommandBase::parsimUnpack(omnetpp::cCommBuffer *b)
{
}

class ndnSocketCommandBaseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    ndnSocketCommandBaseDescriptor();
    virtual ~ndnSocketCommandBaseDescriptor();

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

Register_ClassDescriptor(ndnSocketCommandBaseDescriptor)

ndnSocketCommandBaseDescriptor::ndnSocketCommandBaseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketCommandBase)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

ndnSocketCommandBaseDescriptor::~ndnSocketCommandBaseDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketCommandBaseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketCommandBase *>(obj)!=nullptr;
}

const char **ndnSocketCommandBaseDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketCommandBaseDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketCommandBaseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int ndnSocketCommandBaseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *ndnSocketCommandBaseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int ndnSocketCommandBaseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketCommandBaseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **ndnSocketCommandBaseDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketCommandBaseDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketCommandBaseDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCommandBase *pp = (ndnSocketCommandBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketCommandBaseDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCommandBase *pp = (ndnSocketCommandBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ndnSocketCommandBaseDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCommandBase *pp = (ndnSocketCommandBase *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ndnSocketCommandBaseDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCommandBase *pp = (ndnSocketCommandBase *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ndnSocketCommandBaseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *ndnSocketCommandBaseDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCommandBase *pp = (ndnSocketCommandBase *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ndnSocketBindCommand)

ndnSocketBindCommand::ndnSocketBindCommand() : ::inet::ndnSocketCommandBase()
{
}

ndnSocketBindCommand::ndnSocketBindCommand(const ndnSocketBindCommand& other) : ::inet::ndnSocketCommandBase(other)
{
    copy(other);
}

ndnSocketBindCommand::~ndnSocketBindCommand()
{
}

ndnSocketBindCommand& ndnSocketBindCommand::operator=(const ndnSocketBindCommand& other)
{
    if (this == &other) return *this;
    ::inet::ndnSocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketBindCommand::copy(const ndnSocketBindCommand& other)
{
    this->protocol = other.protocol;
    this->localPort = other.localPort;
    this->nid = other.nid;
}

void ndnSocketBindCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndnSocketCommandBase::parsimPack(b);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->nid);
}

void ndnSocketBindCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndnSocketCommandBase::parsimUnpack(b);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->nid);
}

const Protocol * ndnSocketBindCommand::getProtocol() const
{
    return this->protocol;
}

void ndnSocketBindCommand::setProtocol(const Protocol * protocol)
{
    this->protocol = protocol;
}

int ndnSocketBindCommand::getLocalPort() const
{
    return this->localPort;
}

void ndnSocketBindCommand::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

const iName& ndnSocketBindCommand::getNid() const
{
    return this->nid;
}

void ndnSocketBindCommand::setNid(const iName& nid)
{
    this->nid = nid;
}

class ndnSocketBindCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_protocol,
        FIELD_localPort,
        FIELD_nid,
    };
  public:
    ndnSocketBindCommandDescriptor();
    virtual ~ndnSocketBindCommandDescriptor();

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

Register_ClassDescriptor(ndnSocketBindCommandDescriptor)

ndnSocketBindCommandDescriptor::ndnSocketBindCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketBindCommand)), "inet::ndnSocketCommandBase")
{
    propertynames = nullptr;
}

ndnSocketBindCommandDescriptor::~ndnSocketBindCommandDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketBindCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketBindCommand *>(obj)!=nullptr;
}

const char **ndnSocketBindCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketBindCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketBindCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ndnSocketBindCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_protocol
        FD_ISEDITABLE,    // FIELD_localPort
        0,    // FIELD_nid
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ndnSocketBindCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "protocol",
        "localPort",
        "nid",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ndnSocketBindCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "protocol") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+1;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nid") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketBindCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::Protocol",    // FIELD_protocol
        "int",    // FIELD_localPort
        "inet::iName",    // FIELD_nid
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ndnSocketBindCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketBindCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketBindCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketBindCommand *pp = (ndnSocketBindCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketBindCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketBindCommand *pp = (ndnSocketBindCommand *)object; (void)pp;
    switch (field) {
        case FIELD_protocol: { const Protocol * value = pp->getProtocol(); return omnetpp::opp_typename(typeid(*const_cast<Protocol *>(value))); }
        default: return nullptr;
    }
}

std::string ndnSocketBindCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketBindCommand *pp = (ndnSocketBindCommand *)object; (void)pp;
    switch (field) {
        case FIELD_protocol: {std::stringstream out; out << pp->getProtocol(); return out.str();}
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_nid: {std::stringstream out; out << pp->getNid(); return out.str();}
        default: return "";
    }
}

bool ndnSocketBindCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketBindCommand *pp = (ndnSocketBindCommand *)object; (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        default: return false;
    }
}

const char *ndnSocketBindCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_protocol: return omnetpp::opp_typename(typeid(Protocol));
        default: return nullptr;
    };
}

void *ndnSocketBindCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketBindCommand *pp = (ndnSocketBindCommand *)object; (void)pp;
    switch (field) {
        case FIELD_protocol: return toVoidPtr(pp->getProtocol()); break;
        case FIELD_nid: return toVoidPtr(&pp->getNid()); break;
        default: return nullptr;
    }
}

Register_Class(ndnSocketSendInterestCommand)

ndnSocketSendInterestCommand::ndnSocketSendInterestCommand() : ::inet::ndnSocketCommandBase()
{
}

ndnSocketSendInterestCommand::ndnSocketSendInterestCommand(const ndnSocketSendInterestCommand& other) : ::inet::ndnSocketCommandBase(other)
{
    copy(other);
}

ndnSocketSendInterestCommand::~ndnSocketSendInterestCommand()
{
}

ndnSocketSendInterestCommand& ndnSocketSendInterestCommand::operator=(const ndnSocketSendInterestCommand& other)
{
    if (this == &other) return *this;
    ::inet::ndnSocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketSendInterestCommand::copy(const ndnSocketSendInterestCommand& other)
{
    this->interest = other.interest;
    this->localPort = other.localPort;
    this->Inter = other.Inter;
}

void ndnSocketSendInterestCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndnSocketCommandBase::parsimPack(b);
    doParsimPacking(b,this->interest);
    doParsimPacking(b,this->localPort);
    doParsimPacking(b,this->Inter);
}

void ndnSocketSendInterestCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndnSocketCommandBase::parsimUnpack(b);
    doParsimUnpacking(b,this->interest);
    doParsimUnpacking(b,this->localPort);
    doParsimUnpacking(b,this->Inter);
}

const iName& ndnSocketSendInterestCommand::getInterest() const
{
    return this->interest;
}

void ndnSocketSendInterestCommand::setInterest(const iName& interest)
{
    this->interest = interest;
}

int ndnSocketSendInterestCommand::getLocalPort() const
{
    return this->localPort;
}

void ndnSocketSendInterestCommand::setLocalPort(int localPort)
{
    this->localPort = localPort;
}

double ndnSocketSendInterestCommand::getInter() const
{
    return this->Inter;
}

void ndnSocketSendInterestCommand::setInter(double Inter)
{
    this->Inter = Inter;
}

class ndnSocketSendInterestCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interest,
        FIELD_localPort,
        FIELD_Inter,
    };
  public:
    ndnSocketSendInterestCommandDescriptor();
    virtual ~ndnSocketSendInterestCommandDescriptor();

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

Register_ClassDescriptor(ndnSocketSendInterestCommandDescriptor)

ndnSocketSendInterestCommandDescriptor::ndnSocketSendInterestCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketSendInterestCommand)), "inet::ndnSocketCommandBase")
{
    propertynames = nullptr;
}

ndnSocketSendInterestCommandDescriptor::~ndnSocketSendInterestCommandDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketSendInterestCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketSendInterestCommand *>(obj)!=nullptr;
}

const char **ndnSocketSendInterestCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketSendInterestCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketSendInterestCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ndnSocketSendInterestCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_interest
        FD_ISEDITABLE,    // FIELD_localPort
        FD_ISEDITABLE,    // FIELD_Inter
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ndnSocketSendInterestCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interest",
        "localPort",
        "Inter",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ndnSocketSendInterestCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interest") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "localPort") == 0) return base+1;
    if (fieldName[0] == 'I' && strcmp(fieldName, "Inter") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketSendInterestCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_interest
        "int",    // FIELD_localPort
        "double",    // FIELD_Inter
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ndnSocketSendInterestCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketSendInterestCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketSendInterestCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketSendInterestCommand *pp = (ndnSocketSendInterestCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketSendInterestCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketSendInterestCommand *pp = (ndnSocketSendInterestCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ndnSocketSendInterestCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketSendInterestCommand *pp = (ndnSocketSendInterestCommand *)object; (void)pp;
    switch (field) {
        case FIELD_interest: {std::stringstream out; out << pp->getInterest(); return out.str();}
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_Inter: return double2string(pp->getInter());
        default: return "";
    }
}

bool ndnSocketSendInterestCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketSendInterestCommand *pp = (ndnSocketSendInterestCommand *)object; (void)pp;
    switch (field) {
        case FIELD_localPort: pp->setLocalPort(string2long(value)); return true;
        case FIELD_Inter: pp->setInter(string2double(value)); return true;
        default: return false;
    }
}

const char *ndnSocketSendInterestCommandDescriptor::getFieldStructName(int field) const
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

void *ndnSocketSendInterestCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketSendInterestCommand *pp = (ndnSocketSendInterestCommand *)object; (void)pp;
    switch (field) {
        case FIELD_interest: return toVoidPtr(&pp->getInterest()); break;
        default: return nullptr;
    }
}

Register_Class(ndnSocketCacheDataCommand)

ndnSocketCacheDataCommand::ndnSocketCacheDataCommand() : ::inet::ndnSocketCommandBase()
{
}

ndnSocketCacheDataCommand::ndnSocketCacheDataCommand(const ndnSocketCacheDataCommand& other) : ::inet::ndnSocketCommandBase(other)
{
    copy(other);
}

ndnSocketCacheDataCommand::~ndnSocketCacheDataCommand()
{
}

ndnSocketCacheDataCommand& ndnSocketCacheDataCommand::operator=(const ndnSocketCacheDataCommand& other)
{
    if (this == &other) return *this;
    ::inet::ndnSocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketCacheDataCommand::copy(const ndnSocketCacheDataCommand& other)
{
    this->interest = other.interest;
    this->pkt = other.pkt;
}

void ndnSocketCacheDataCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndnSocketCommandBase::parsimPack(b);
    doParsimPacking(b,this->interest);
    doParsimPacking(b,this->pkt);
}

void ndnSocketCacheDataCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndnSocketCommandBase::parsimUnpack(b);
    doParsimUnpacking(b,this->interest);
    doParsimUnpacking(b,this->pkt);
}

const iName& ndnSocketCacheDataCommand::getInterest() const
{
    return this->interest;
}

void ndnSocketCacheDataCommand::setInterest(const iName& interest)
{
    this->interest = interest;
}

const cMessage * ndnSocketCacheDataCommand::getPkt() const
{
    return this->pkt;
}

void ndnSocketCacheDataCommand::setPkt(cMessage * pkt)
{
    this->pkt = pkt;
}

class ndnSocketCacheDataCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interest,
        FIELD_pkt,
    };
  public:
    ndnSocketCacheDataCommandDescriptor();
    virtual ~ndnSocketCacheDataCommandDescriptor();

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

Register_ClassDescriptor(ndnSocketCacheDataCommandDescriptor)

ndnSocketCacheDataCommandDescriptor::ndnSocketCacheDataCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketCacheDataCommand)), "inet::ndnSocketCommandBase")
{
    propertynames = nullptr;
}

ndnSocketCacheDataCommandDescriptor::~ndnSocketCacheDataCommandDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketCacheDataCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketCacheDataCommand *>(obj)!=nullptr;
}

const char **ndnSocketCacheDataCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketCacheDataCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketCacheDataCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int ndnSocketCacheDataCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_interest
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,    // FIELD_pkt
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *ndnSocketCacheDataCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interest",
        "pkt",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int ndnSocketCacheDataCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interest") == 0) return base+0;
    if (fieldName[0] == 'p' && strcmp(fieldName, "pkt") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketCacheDataCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_interest
        "omnetpp::cMessage",    // FIELD_pkt
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **ndnSocketCacheDataCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketCacheDataCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketCacheDataCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCacheDataCommand *pp = (ndnSocketCacheDataCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketCacheDataCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCacheDataCommand *pp = (ndnSocketCacheDataCommand *)object; (void)pp;
    switch (field) {
        case FIELD_pkt: { const cMessage * value = pp->getPkt(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string ndnSocketCacheDataCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCacheDataCommand *pp = (ndnSocketCacheDataCommand *)object; (void)pp;
    switch (field) {
        case FIELD_interest: {std::stringstream out; out << pp->getInterest(); return out.str();}
        case FIELD_pkt: {std::stringstream out; out << pp->getPkt(); return out.str();}
        default: return "";
    }
}

bool ndnSocketCacheDataCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCacheDataCommand *pp = (ndnSocketCacheDataCommand *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ndnSocketCacheDataCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_pkt: return omnetpp::opp_typename(typeid(cMessage));
        default: return nullptr;
    };
}

void *ndnSocketCacheDataCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCacheDataCommand *pp = (ndnSocketCacheDataCommand *)object; (void)pp;
    switch (field) {
        case FIELD_interest: return toVoidPtr(&pp->getInterest()); break;
        case FIELD_pkt: return toVoidPtr(pp->getPkt()); break;
        default: return nullptr;
    }
}

Register_Class(ndnSocketCloseCommand)

ndnSocketCloseCommand::ndnSocketCloseCommand() : ::inet::ndnSocketCommandBase()
{
}

ndnSocketCloseCommand::ndnSocketCloseCommand(const ndnSocketCloseCommand& other) : ::inet::ndnSocketCommandBase(other)
{
    copy(other);
}

ndnSocketCloseCommand::~ndnSocketCloseCommand()
{
}

ndnSocketCloseCommand& ndnSocketCloseCommand::operator=(const ndnSocketCloseCommand& other)
{
    if (this == &other) return *this;
    ::inet::ndnSocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketCloseCommand::copy(const ndnSocketCloseCommand& other)
{
}

void ndnSocketCloseCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndnSocketCommandBase::parsimPack(b);
}

void ndnSocketCloseCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndnSocketCommandBase::parsimUnpack(b);
}

class ndnSocketCloseCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    ndnSocketCloseCommandDescriptor();
    virtual ~ndnSocketCloseCommandDescriptor();

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

Register_ClassDescriptor(ndnSocketCloseCommandDescriptor)

ndnSocketCloseCommandDescriptor::ndnSocketCloseCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketCloseCommand)), "inet::ndnSocketCommandBase")
{
    propertynames = nullptr;
}

ndnSocketCloseCommandDescriptor::~ndnSocketCloseCommandDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketCloseCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketCloseCommand *>(obj)!=nullptr;
}

const char **ndnSocketCloseCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketCloseCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketCloseCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int ndnSocketCloseCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *ndnSocketCloseCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int ndnSocketCloseCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketCloseCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **ndnSocketCloseCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketCloseCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketCloseCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCloseCommand *pp = (ndnSocketCloseCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketCloseCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCloseCommand *pp = (ndnSocketCloseCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ndnSocketCloseCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCloseCommand *pp = (ndnSocketCloseCommand *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ndnSocketCloseCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCloseCommand *pp = (ndnSocketCloseCommand *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ndnSocketCloseCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *ndnSocketCloseCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketCloseCommand *pp = (ndnSocketCloseCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ndnSocketDestroyCommand)

ndnSocketDestroyCommand::ndnSocketDestroyCommand() : ::inet::ndnSocketCommandBase()
{
}

ndnSocketDestroyCommand::ndnSocketDestroyCommand(const ndnSocketDestroyCommand& other) : ::inet::ndnSocketCommandBase(other)
{
    copy(other);
}

ndnSocketDestroyCommand::~ndnSocketDestroyCommand()
{
}

ndnSocketDestroyCommand& ndnSocketDestroyCommand::operator=(const ndnSocketDestroyCommand& other)
{
    if (this == &other) return *this;
    ::inet::ndnSocketCommandBase::operator=(other);
    copy(other);
    return *this;
}

void ndnSocketDestroyCommand::copy(const ndnSocketDestroyCommand& other)
{
}

void ndnSocketDestroyCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ndnSocketCommandBase::parsimPack(b);
}

void ndnSocketDestroyCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ndnSocketCommandBase::parsimUnpack(b);
}

class ndnSocketDestroyCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    ndnSocketDestroyCommandDescriptor();
    virtual ~ndnSocketDestroyCommandDescriptor();

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

Register_ClassDescriptor(ndnSocketDestroyCommandDescriptor)

ndnSocketDestroyCommandDescriptor::ndnSocketDestroyCommandDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::ndnSocketDestroyCommand)), "inet::ndnSocketCommandBase")
{
    propertynames = nullptr;
}

ndnSocketDestroyCommandDescriptor::~ndnSocketDestroyCommandDescriptor()
{
    delete[] propertynames;
}

bool ndnSocketDestroyCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ndnSocketDestroyCommand *>(obj)!=nullptr;
}

const char **ndnSocketDestroyCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ndnSocketDestroyCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ndnSocketDestroyCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int ndnSocketDestroyCommandDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *ndnSocketDestroyCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int ndnSocketDestroyCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ndnSocketDestroyCommandDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **ndnSocketDestroyCommandDescriptor::getFieldPropertyNames(int field) const
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

const char *ndnSocketDestroyCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ndnSocketDestroyCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ndnSocketDestroyCommand *pp = (ndnSocketDestroyCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *ndnSocketDestroyCommandDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketDestroyCommand *pp = (ndnSocketDestroyCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ndnSocketDestroyCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketDestroyCommand *pp = (ndnSocketDestroyCommand *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool ndnSocketDestroyCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ndnSocketDestroyCommand *pp = (ndnSocketDestroyCommand *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *ndnSocketDestroyCommandDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *ndnSocketDestroyCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ndnSocketDestroyCommand *pp = (ndnSocketDestroyCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

} // namespace inet

