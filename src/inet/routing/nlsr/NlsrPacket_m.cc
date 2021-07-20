//
// Generated file, do not edit! Created by nedtool 5.6 from inet/routing/nlsr/NlsrPacket.msg.
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
#include "NlsrPacket_m.h"

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

class inet__nlsr__IBLTDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    inet__nlsr__IBLTDescriptor();
    virtual ~inet__nlsr__IBLTDescriptor();

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

Register_ClassDescriptor(inet__nlsr__IBLTDescriptor)

inet__nlsr__IBLTDescriptor::inet__nlsr__IBLTDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::IBLT)), "")
{
    propertynames = nullptr;
}

inet__nlsr__IBLTDescriptor::~inet__nlsr__IBLTDescriptor()
{
    delete[] propertynames;
}

bool inet__nlsr__IBLTDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<inet::nlsr::IBLT *>(obj)!=nullptr;
}

const char **inet__nlsr__IBLTDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *inet__nlsr__IBLTDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int inet__nlsr__IBLTDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int inet__nlsr__IBLTDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *inet__nlsr__IBLTDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int inet__nlsr__IBLTDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *inet__nlsr__IBLTDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **inet__nlsr__IBLTDescriptor::getFieldPropertyNames(int field) const
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

const char *inet__nlsr__IBLTDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int inet__nlsr__IBLTDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::IBLT *pp = (inet::nlsr::IBLT *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *inet__nlsr__IBLTDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::IBLT *pp = (inet::nlsr::IBLT *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string inet__nlsr__IBLTDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::IBLT *pp = (inet::nlsr::IBLT *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool inet__nlsr__IBLTDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::IBLT *pp = (inet::nlsr::IBLT *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *inet__nlsr__IBLTDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *inet__nlsr__IBLTDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::IBLT *pp = (inet::nlsr::IBLT *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

class inet__nlsr__AdjacencyListDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    inet__nlsr__AdjacencyListDescriptor();
    virtual ~inet__nlsr__AdjacencyListDescriptor();

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

Register_ClassDescriptor(inet__nlsr__AdjacencyListDescriptor)

inet__nlsr__AdjacencyListDescriptor::inet__nlsr__AdjacencyListDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::AdjacencyList)), "")
{
    propertynames = nullptr;
}

inet__nlsr__AdjacencyListDescriptor::~inet__nlsr__AdjacencyListDescriptor()
{
    delete[] propertynames;
}

bool inet__nlsr__AdjacencyListDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<inet::nlsr::AdjacencyList *>(obj)!=nullptr;
}

const char **inet__nlsr__AdjacencyListDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *inet__nlsr__AdjacencyListDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int inet__nlsr__AdjacencyListDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int inet__nlsr__AdjacencyListDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *inet__nlsr__AdjacencyListDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int inet__nlsr__AdjacencyListDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *inet__nlsr__AdjacencyListDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **inet__nlsr__AdjacencyListDescriptor::getFieldPropertyNames(int field) const
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

const char *inet__nlsr__AdjacencyListDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int inet__nlsr__AdjacencyListDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::AdjacencyList *pp = (inet::nlsr::AdjacencyList *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *inet__nlsr__AdjacencyListDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::AdjacencyList *pp = (inet::nlsr::AdjacencyList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string inet__nlsr__AdjacencyListDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::AdjacencyList *pp = (inet::nlsr::AdjacencyList *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool inet__nlsr__AdjacencyListDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::AdjacencyList *pp = (inet::nlsr::AdjacencyList *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *inet__nlsr__AdjacencyListDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *inet__nlsr__AdjacencyListDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::AdjacencyList *pp = (inet::nlsr::AdjacencyList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

class inet__nlsr__NamePrefixListDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    inet__nlsr__NamePrefixListDescriptor();
    virtual ~inet__nlsr__NamePrefixListDescriptor();

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

Register_ClassDescriptor(inet__nlsr__NamePrefixListDescriptor)

inet__nlsr__NamePrefixListDescriptor::inet__nlsr__NamePrefixListDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NamePrefixList)), "")
{
    propertynames = nullptr;
}

inet__nlsr__NamePrefixListDescriptor::~inet__nlsr__NamePrefixListDescriptor()
{
    delete[] propertynames;
}

bool inet__nlsr__NamePrefixListDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<inet::nlsr::NamePrefixList *>(obj)!=nullptr;
}

const char **inet__nlsr__NamePrefixListDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *inet__nlsr__NamePrefixListDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname, "existingClass")) return "";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int inet__nlsr__NamePrefixListDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int inet__nlsr__NamePrefixListDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *inet__nlsr__NamePrefixListDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int inet__nlsr__NamePrefixListDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *inet__nlsr__NamePrefixListDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **inet__nlsr__NamePrefixListDescriptor::getFieldPropertyNames(int field) const
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

const char *inet__nlsr__NamePrefixListDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int inet__nlsr__NamePrefixListDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::NamePrefixList *pp = (inet::nlsr::NamePrefixList *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *inet__nlsr__NamePrefixListDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::NamePrefixList *pp = (inet::nlsr::NamePrefixList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string inet__nlsr__NamePrefixListDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::NamePrefixList *pp = (inet::nlsr::NamePrefixList *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool inet__nlsr__NamePrefixListDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::NamePrefixList *pp = (inet::nlsr::NamePrefixList *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *inet__nlsr__NamePrefixListDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *inet__nlsr__NamePrefixListDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    inet::nlsr::NamePrefixList *pp = (inet::nlsr::NamePrefixList *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

namespace inet {
namespace nlsr {

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::nlsr::NlsrTimerType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::nlsr::NlsrTimerType"));
    e->insert(INTERFACE_HELLO_TIMER, "INTERFACE_HELLO_TIMER");
    e->insert(NEIGHBOR_INACTIVITY_TIMER, "NEIGHBOR_INACTIVITY_TIMER");
    e->insert(NEIGHBOR_POLL_TIMER, "NEIGHBOR_POLL_TIMER");
    e->insert(DATABASE_AGE_TIMER, "DATABASE_AGE_TIMER");
    e->insert(SYNC_START_TIMER, "SYNC_START_TIMER");
)

Register_Class(NlsrPacket)

NlsrPacket::NlsrPacket() : ::inet::nlsr::NlsrPacketBase()
{
    this->setChunkLength(B(48));
    this->setVersion(2);
}

NlsrPacket::NlsrPacket(const NlsrPacket& other) : ::inet::nlsr::NlsrPacketBase(other)
{
    copy(other);
}

NlsrPacket::~NlsrPacket()
{
}

NlsrPacket& NlsrPacket::operator=(const NlsrPacket& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacketBase::operator=(other);
    copy(other);
    return *this;
}

void NlsrPacket::copy(const NlsrPacket& other)
{
}

void NlsrPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacketBase::parsimPack(b);
}

void NlsrPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacketBase::parsimUnpack(b);
}

class NlsrPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
    };
  public:
    NlsrPacketDescriptor();
    virtual ~NlsrPacketDescriptor();

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

Register_ClassDescriptor(NlsrPacketDescriptor)

NlsrPacketDescriptor::NlsrPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrPacket)), "inet::nlsr::NlsrPacketBase")
{
    propertynames = nullptr;
}

NlsrPacketDescriptor::~NlsrPacketDescriptor()
{
    delete[] propertynames;
}

bool NlsrPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrPacket *>(obj)!=nullptr;
}

const char **NlsrPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount() : 0;
}

unsigned int NlsrPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    return 0;
}

const char *NlsrPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

int NlsrPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

const char **NlsrPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *NlsrPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NlsrPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrPacket *pp = (NlsrPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrPacket *pp = (NlsrPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrPacket *pp = (NlsrPacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool NlsrPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrPacket *pp = (NlsrPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NlsrPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    return nullptr;
}

void *NlsrPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrPacket *pp = (NlsrPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NlsrHelloInterest)

NlsrHelloInterest::NlsrHelloInterest() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(100));
    this->setType(HELLO_INTEREST);

}

NlsrHelloInterest::NlsrHelloInterest(const NlsrHelloInterest& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

NlsrHelloInterest::~NlsrHelloInterest()
{
}

NlsrHelloInterest& NlsrHelloInterest::operator=(const NlsrHelloInterest& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void NlsrHelloInterest::copy(const NlsrHelloInterest& other)
{
    this->helloInterval = other.helloInterval;
    this->routerDeadInterval = other.routerDeadInterval;
    this->hopCount = other.hopCount;
    this->seqNo = other.seqNo;
    this->canBePrefix = other.canBePrefix;
    this->MustBeFresh = other.MustBeFresh;
    this->interestLifetimeMs = other.interestLifetimeMs;
    this->hopLimit = other.hopLimit;
}

void NlsrHelloInterest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->helloInterval);
    doParsimPacking(b,this->routerDeadInterval);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->canBePrefix);
    doParsimPacking(b,this->MustBeFresh);
    doParsimPacking(b,this->interestLifetimeMs);
    doParsimPacking(b,this->hopLimit);
}

void NlsrHelloInterest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->helloInterval);
    doParsimUnpacking(b,this->routerDeadInterval);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->canBePrefix);
    doParsimUnpacking(b,this->MustBeFresh);
    doParsimUnpacking(b,this->interestLifetimeMs);
    doParsimUnpacking(b,this->hopLimit);
}

short NlsrHelloInterest::getHelloInterval() const
{
    return this->helloInterval;
}

void NlsrHelloInterest::setHelloInterval(short helloInterval)
{
    handleChange();
    this->helloInterval = helloInterval;
}

double NlsrHelloInterest::getRouterDeadInterval() const
{
    return this->routerDeadInterval;
}

void NlsrHelloInterest::setRouterDeadInterval(double routerDeadInterval)
{
    handleChange();
    this->routerDeadInterval = routerDeadInterval;
}

int NlsrHelloInterest::getHopCount() const
{
    return this->hopCount;
}

void NlsrHelloInterest::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

long NlsrHelloInterest::getSeqNo() const
{
    return this->seqNo;
}

void NlsrHelloInterest::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

bool NlsrHelloInterest::getCanBePrefix() const
{
    return this->canBePrefix;
}

void NlsrHelloInterest::setCanBePrefix(bool canBePrefix)
{
    handleChange();
    this->canBePrefix = canBePrefix;
}

bool NlsrHelloInterest::getMustBeFresh() const
{
    return this->MustBeFresh;
}

void NlsrHelloInterest::setMustBeFresh(bool MustBeFresh)
{
    handleChange();
    this->MustBeFresh = MustBeFresh;
}

unsigned int NlsrHelloInterest::getInterestLifetimeMs() const
{
    return this->interestLifetimeMs;
}

void NlsrHelloInterest::setInterestLifetimeMs(unsigned int interestLifetimeMs)
{
    handleChange();
    this->interestLifetimeMs = interestLifetimeMs;
}

unsigned int NlsrHelloInterest::getHopLimit() const
{
    return this->hopLimit;
}

void NlsrHelloInterest::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

class NlsrHelloInterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_helloInterval,
        FIELD_routerDeadInterval,
        FIELD_hopCount,
        FIELD_seqNo,
        FIELD_canBePrefix,
        FIELD_MustBeFresh,
        FIELD_interestLifetimeMs,
        FIELD_hopLimit,
    };
  public:
    NlsrHelloInterestDescriptor();
    virtual ~NlsrHelloInterestDescriptor();

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

Register_ClassDescriptor(NlsrHelloInterestDescriptor)

NlsrHelloInterestDescriptor::NlsrHelloInterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrHelloInterest)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

NlsrHelloInterestDescriptor::~NlsrHelloInterestDescriptor()
{
    delete[] propertynames;
}

bool NlsrHelloInterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrHelloInterest *>(obj)!=nullptr;
}

const char **NlsrHelloInterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrHelloInterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrHelloInterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int NlsrHelloInterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_helloInterval
        FD_ISEDITABLE,    // FIELD_routerDeadInterval
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_canBePrefix
        FD_ISEDITABLE,    // FIELD_MustBeFresh
        FD_ISEDITABLE,    // FIELD_interestLifetimeMs
        FD_ISEDITABLE,    // FIELD_hopLimit
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *NlsrHelloInterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "helloInterval",
        "routerDeadInterval",
        "hopCount",
        "seqNo",
        "canBePrefix",
        "MustBeFresh",
        "interestLifetimeMs",
        "hopLimit",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int NlsrHelloInterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "helloInterval") == 0) return base+0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerDeadInterval") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "canBePrefix") == 0) return base+4;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MustBeFresh") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestLifetimeMs") == 0) return base+6;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrHelloInterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "short",    // FIELD_helloInterval
        "double",    // FIELD_routerDeadInterval
        "int",    // FIELD_hopCount
        "long",    // FIELD_seqNo
        "bool",    // FIELD_canBePrefix
        "bool",    // FIELD_MustBeFresh
        "unsigned int",    // FIELD_interestLifetimeMs
        "unsigned int",    // FIELD_hopLimit
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrHelloInterestDescriptor::getFieldPropertyNames(int field) const
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

const char *NlsrHelloInterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NlsrHelloInterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloInterest *pp = (NlsrHelloInterest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrHelloInterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloInterest *pp = (NlsrHelloInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrHelloInterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloInterest *pp = (NlsrHelloInterest *)object; (void)pp;
    switch (field) {
        case FIELD_helloInterval: return long2string(pp->getHelloInterval());
        case FIELD_routerDeadInterval: return double2string(pp->getRouterDeadInterval());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_canBePrefix: return bool2string(pp->getCanBePrefix());
        case FIELD_MustBeFresh: return bool2string(pp->getMustBeFresh());
        case FIELD_interestLifetimeMs: return ulong2string(pp->getInterestLifetimeMs());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        default: return "";
    }
}

bool NlsrHelloInterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloInterest *pp = (NlsrHelloInterest *)object; (void)pp;
    switch (field) {
        case FIELD_helloInterval: pp->setHelloInterval(string2long(value)); return true;
        case FIELD_routerDeadInterval: pp->setRouterDeadInterval(string2double(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_canBePrefix: pp->setCanBePrefix(string2bool(value)); return true;
        case FIELD_MustBeFresh: pp->setMustBeFresh(string2bool(value)); return true;
        case FIELD_interestLifetimeMs: pp->setInterestLifetimeMs(string2ulong(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NlsrHelloInterestDescriptor::getFieldStructName(int field) const
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

void *NlsrHelloInterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloInterest *pp = (NlsrHelloInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(NlsrHelloData)

NlsrHelloData::NlsrHelloData() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(100));
    this->setType(HELLO_DATA);

}

NlsrHelloData::NlsrHelloData(const NlsrHelloData& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

NlsrHelloData::~NlsrHelloData()
{
}

NlsrHelloData& NlsrHelloData::operator=(const NlsrHelloData& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void NlsrHelloData::copy(const NlsrHelloData& other)
{
    this->routerDeadInterval = other.routerDeadInterval;
    this->hopCount = other.hopCount;
    this->seqNo = other.seqNo;
    this->hopLimit = other.hopLimit;
}

void NlsrHelloData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->routerDeadInterval);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->hopLimit);
}

void NlsrHelloData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->routerDeadInterval);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->hopLimit);
}

double NlsrHelloData::getRouterDeadInterval() const
{
    return this->routerDeadInterval;
}

void NlsrHelloData::setRouterDeadInterval(double routerDeadInterval)
{
    handleChange();
    this->routerDeadInterval = routerDeadInterval;
}

int NlsrHelloData::getHopCount() const
{
    return this->hopCount;
}

void NlsrHelloData::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

long NlsrHelloData::getSeqNo() const
{
    return this->seqNo;
}

void NlsrHelloData::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

unsigned int NlsrHelloData::getHopLimit() const
{
    return this->hopLimit;
}

void NlsrHelloData::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

class NlsrHelloDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_routerDeadInterval,
        FIELD_hopCount,
        FIELD_seqNo,
        FIELD_hopLimit,
    };
  public:
    NlsrHelloDataDescriptor();
    virtual ~NlsrHelloDataDescriptor();

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

Register_ClassDescriptor(NlsrHelloDataDescriptor)

NlsrHelloDataDescriptor::NlsrHelloDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrHelloData)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

NlsrHelloDataDescriptor::~NlsrHelloDataDescriptor()
{
    delete[] propertynames;
}

bool NlsrHelloDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrHelloData *>(obj)!=nullptr;
}

const char **NlsrHelloDataDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrHelloDataDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrHelloDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int NlsrHelloDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_routerDeadInterval
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_hopLimit
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *NlsrHelloDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "routerDeadInterval",
        "hopCount",
        "seqNo",
        "hopLimit",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int NlsrHelloDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'r' && strcmp(fieldName, "routerDeadInterval") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+2;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrHelloDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_routerDeadInterval
        "int",    // FIELD_hopCount
        "long",    // FIELD_seqNo
        "unsigned int",    // FIELD_hopLimit
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrHelloDataDescriptor::getFieldPropertyNames(int field) const
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

const char *NlsrHelloDataDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NlsrHelloDataDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloData *pp = (NlsrHelloData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrHelloDataDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloData *pp = (NlsrHelloData *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrHelloDataDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloData *pp = (NlsrHelloData *)object; (void)pp;
    switch (field) {
        case FIELD_routerDeadInterval: return double2string(pp->getRouterDeadInterval());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        default: return "";
    }
}

bool NlsrHelloDataDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloData *pp = (NlsrHelloData *)object; (void)pp;
    switch (field) {
        case FIELD_routerDeadInterval: pp->setRouterDeadInterval(string2double(value)); return true;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NlsrHelloDataDescriptor::getFieldStructName(int field) const
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

void *NlsrHelloDataDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrHelloData *pp = (NlsrHelloData *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(syncInterest)

syncInterest::syncInterest() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1300));
    this->setType(SYNC_INTEREST);

}

syncInterest::syncInterest(const syncInterest& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

syncInterest::~syncInterest()
{
}

syncInterest& syncInterest::operator=(const syncInterest& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void syncInterest::copy(const syncInterest& other)
{
    this->m_iblt = other.m_iblt;
    this->seqNo = other.seqNo;
    this->interestLifetimeMs = other.interestLifetimeMs;
}

void syncInterest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->m_iblt);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->interestLifetimeMs);
}

void syncInterest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->m_iblt);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->interestLifetimeMs);
}

const inet::nlsr::IBLT& syncInterest::getM_iblt() const
{
    return this->m_iblt;
}

void syncInterest::setM_iblt(const inet::nlsr::IBLT& m_iblt)
{
    handleChange();
    this->m_iblt = m_iblt;
}

long syncInterest::getSeqNo() const
{
    return this->seqNo;
}

void syncInterest::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

unsigned int syncInterest::getInterestLifetimeMs() const
{
    return this->interestLifetimeMs;
}

void syncInterest::setInterestLifetimeMs(unsigned int interestLifetimeMs)
{
    handleChange();
    this->interestLifetimeMs = interestLifetimeMs;
}

class syncInterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_m_iblt,
        FIELD_seqNo,
        FIELD_interestLifetimeMs,
    };
  public:
    syncInterestDescriptor();
    virtual ~syncInterestDescriptor();

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

Register_ClassDescriptor(syncInterestDescriptor)

syncInterestDescriptor::syncInterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::syncInterest)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

syncInterestDescriptor::~syncInterestDescriptor()
{
    delete[] propertynames;
}

bool syncInterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<syncInterest *>(obj)!=nullptr;
}

const char **syncInterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *syncInterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int syncInterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int syncInterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,    // FIELD_m_iblt
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *syncInterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "m_iblt",
        "seqNo",
        "interestLifetimeMs",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int syncInterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "m_iblt") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+1;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestLifetimeMs") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *syncInterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::IBLT",    // FIELD_m_iblt
        "long",    // FIELD_seqNo
        "unsigned int",    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **syncInterestDescriptor::getFieldPropertyNames(int field) const
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

const char *syncInterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int syncInterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    syncInterest *pp = (syncInterest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *syncInterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    syncInterest *pp = (syncInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string syncInterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    syncInterest *pp = (syncInterest *)object; (void)pp;
    switch (field) {
        case FIELD_m_iblt: {std::stringstream out; out << pp->getM_iblt(); return out.str();}
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_interestLifetimeMs: return ulong2string(pp->getInterestLifetimeMs());
        default: return "";
    }
}

bool syncInterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    syncInterest *pp = (syncInterest *)object; (void)pp;
    switch (field) {
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_interestLifetimeMs: pp->setInterestLifetimeMs(string2ulong(value)); return true;
        default: return false;
    }
}

const char *syncInterestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_m_iblt: return omnetpp::opp_typename(typeid(inet::nlsr::IBLT));
        default: return nullptr;
    };
}

void *syncInterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    syncInterest *pp = (syncInterest *)object; (void)pp;
    switch (field) {
        case FIELD_m_iblt: return toVoidPtr(&pp->getM_iblt()); break;
        default: return nullptr;
    }
}

Register_Class(syncData)

syncData::syncData() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1300));
    this->setType(SYNC_DATA);

}

syncData::syncData(const syncData& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

syncData::~syncData()
{
    delete [] this->syncDATA;
}

syncData& syncData::operator=(const syncData& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void syncData::copy(const syncData& other)
{
    this->hopCount = other.hopCount;
    this->seqNo = other.seqNo;
    delete [] this->syncDATA;
    this->syncDATA = (other.syncDATA_arraysize==0) ? nullptr : new iName[other.syncDATA_arraysize];
    syncDATA_arraysize = other.syncDATA_arraysize;
    for (size_t i = 0; i < syncDATA_arraysize; i++) {
        this->syncDATA[i] = other.syncDATA[i];
    }
    this->moreFragments = other.moreFragments;
    this->hopLimit = other.hopLimit;
    this->totalLength = other.totalLength;
}

void syncData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->seqNo);
    b->pack(syncDATA_arraysize);
    doParsimArrayPacking(b,this->syncDATA,syncDATA_arraysize);
    doParsimPacking(b,this->moreFragments);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->totalLength);
}

void syncData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->seqNo);
    delete [] this->syncDATA;
    b->unpack(syncDATA_arraysize);
    if (syncDATA_arraysize == 0) {
        this->syncDATA = nullptr;
    } else {
        this->syncDATA = new iName[syncDATA_arraysize];
        doParsimArrayUnpacking(b,this->syncDATA,syncDATA_arraysize);
    }
    doParsimUnpacking(b,this->moreFragments);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->totalLength);
}

int syncData::getHopCount() const
{
    return this->hopCount;
}

void syncData::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

long syncData::getSeqNo() const
{
    return this->seqNo;
}

void syncData::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

size_t syncData::getSyncDATAArraySize() const
{
    return syncDATA_arraysize;
}

const iName& syncData::getSyncDATA(size_t k) const
{
    if (k >= syncDATA_arraysize) throw omnetpp::cRuntimeError("Array of size syncDATA_arraysize indexed by %lu", (unsigned long)k);
    return this->syncDATA[k];
}

void syncData::setSyncDATAArraySize(size_t newSize)
{
    handleChange();
    iName *syncDATA2 = (newSize==0) ? nullptr : new iName[newSize];
    size_t minSize = syncDATA_arraysize < newSize ? syncDATA_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        syncDATA2[i] = this->syncDATA[i];
    delete [] this->syncDATA;
    this->syncDATA = syncDATA2;
    syncDATA_arraysize = newSize;
}

void syncData::setSyncDATA(size_t k, const iName& syncDATA)
{
    if (k >= syncDATA_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->syncDATA[k] = syncDATA;
}

void syncData::insertSyncDATA(size_t k, const iName& syncDATA)
{
    handleChange();
    if (k > syncDATA_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = syncDATA_arraysize + 1;
    iName *syncDATA2 = new iName[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        syncDATA2[i] = this->syncDATA[i];
    syncDATA2[k] = syncDATA;
    for (i = k + 1; i < newSize; i++)
        syncDATA2[i] = this->syncDATA[i-1];
    delete [] this->syncDATA;
    this->syncDATA = syncDATA2;
    syncDATA_arraysize = newSize;
}

void syncData::insertSyncDATA(const iName& syncDATA)
{
    insertSyncDATA(syncDATA_arraysize, syncDATA);
}

void syncData::eraseSyncDATA(size_t k)
{
    if (k >= syncDATA_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = syncDATA_arraysize - 1;
    iName *syncDATA2 = (newSize == 0) ? nullptr : new iName[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        syncDATA2[i] = this->syncDATA[i];
    for (i = k; i < newSize; i++)
        syncDATA2[i] = this->syncDATA[i+1];
    delete [] this->syncDATA;
    this->syncDATA = syncDATA2;
    syncDATA_arraysize = newSize;
}

bool syncData::getMoreFragments() const
{
    return this->moreFragments;
}

void syncData::setMoreFragments(bool moreFragments)
{
    handleChange();
    this->moreFragments = moreFragments;
}

unsigned int syncData::getHopLimit() const
{
    return this->hopLimit;
}

void syncData::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

long syncData::getTotalLength() const
{
    return this->totalLength;
}

void syncData::setTotalLength(long totalLength)
{
    handleChange();
    this->totalLength = totalLength;
}

class syncDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_hopCount,
        FIELD_seqNo,
        FIELD_syncDATA,
        FIELD_moreFragments,
        FIELD_hopLimit,
        FIELD_totalLength,
    };
  public:
    syncDataDescriptor();
    virtual ~syncDataDescriptor();

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

Register_ClassDescriptor(syncDataDescriptor)

syncDataDescriptor::syncDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::syncData)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

syncDataDescriptor::~syncDataDescriptor()
{
    delete[] propertynames;
}

bool syncDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<syncData *>(obj)!=nullptr;
}

const char **syncDataDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *syncDataDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int syncDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int syncDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISARRAY,    // FIELD_syncDATA
        FD_ISEDITABLE,    // FIELD_moreFragments
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_totalLength
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *syncDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hopCount",
        "seqNo",
        "syncDATA",
        "moreFragments",
        "hopLimit",
        "totalLength",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int syncDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+0;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+1;
    if (fieldName[0] == 's' && strcmp(fieldName, "syncDATA") == 0) return base+2;
    if (fieldName[0] == 'm' && strcmp(fieldName, "moreFragments") == 0) return base+3;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+4;
    if (fieldName[0] == 't' && strcmp(fieldName, "totalLength") == 0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *syncDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_hopCount
        "long",    // FIELD_seqNo
        "inet::iName",    // FIELD_syncDATA
        "bool",    // FIELD_moreFragments
        "unsigned int",    // FIELD_hopLimit
        "long",    // FIELD_totalLength
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **syncDataDescriptor::getFieldPropertyNames(int field) const
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

const char *syncDataDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int syncDataDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    syncData *pp = (syncData *)object; (void)pp;
    switch (field) {
        case FIELD_syncDATA: return pp->getSyncDATAArraySize();
        default: return 0;
    }
}

const char *syncDataDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    syncData *pp = (syncData *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string syncDataDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    syncData *pp = (syncData *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_syncDATA: {std::stringstream out; out << pp->getSyncDATA(i); return out.str();}
        case FIELD_moreFragments: return bool2string(pp->getMoreFragments());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        case FIELD_totalLength: return long2string(pp->getTotalLength());
        default: return "";
    }
}

bool syncDataDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    syncData *pp = (syncData *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_moreFragments: pp->setMoreFragments(string2bool(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        case FIELD_totalLength: pp->setTotalLength(string2long(value)); return true;
        default: return false;
    }
}

const char *syncDataDescriptor::getFieldStructName(int field) const
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

void *syncDataDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    syncData *pp = (syncData *)object; (void)pp;
    switch (field) {
        case FIELD_syncDATA: return toVoidPtr(&pp->getSyncDATA(i)); break;
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::nlsr::LinkType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::nlsr::LinkType"));
    e->insert(POINTTOPOINT_LINK, "POINTTOPOINT_LINK");
)

Register_Class(NlsrLink)

NlsrLink::NlsrLink() : ::omnetpp::cObject()
{
}

NlsrLink::NlsrLink(const NlsrLink& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NlsrLink::~NlsrLink()
{
}

NlsrLink& NlsrLink::operator=(const NlsrLink& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NlsrLink::copy(const NlsrLink& other)
{
    this->linkID = other.linkID;
    this->linkData = other.linkData;
    this->type = other.type;
    this->linkCost = other.linkCost;
}

void NlsrLink::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->linkID);
    doParsimPacking(b,this->linkData);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->linkCost);
}

void NlsrLink::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->linkID);
    doParsimUnpacking(b,this->linkData);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->linkCost);
}

const iName& NlsrLink::getLinkID() const
{
    return this->linkID;
}

void NlsrLink::setLinkID(const iName& linkID)
{
    this->linkID = linkID;
}

unsigned long NlsrLink::getLinkData() const
{
    return this->linkData;
}

void NlsrLink::setLinkData(unsigned long linkData)
{
    this->linkData = linkData;
}

inet::nlsr::LinkType NlsrLink::getType() const
{
    return this->type;
}

void NlsrLink::setType(inet::nlsr::LinkType type)
{
    this->type = type;
}

unsigned long NlsrLink::getLinkCost() const
{
    return this->linkCost;
}

void NlsrLink::setLinkCost(unsigned long linkCost)
{
    this->linkCost = linkCost;
}

class NlsrLinkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_linkID,
        FIELD_linkData,
        FIELD_type,
        FIELD_linkCost,
    };
  public:
    NlsrLinkDescriptor();
    virtual ~NlsrLinkDescriptor();

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

Register_ClassDescriptor(NlsrLinkDescriptor)

NlsrLinkDescriptor::NlsrLinkDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrLink)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NlsrLinkDescriptor::~NlsrLinkDescriptor()
{
    delete[] propertynames;
}

bool NlsrLinkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrLink *>(obj)!=nullptr;
}

const char **NlsrLinkDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrLinkDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrLinkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int NlsrLinkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_linkID
        FD_ISEDITABLE,    // FIELD_linkData
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_linkCost
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *NlsrLinkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "linkID",
        "linkData",
        "type",
        "linkCost",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int NlsrLinkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkID") == 0) return base+0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkData") == 0) return base+1;
    if (fieldName[0] == 't' && strcmp(fieldName, "type") == 0) return base+2;
    if (fieldName[0] == 'l' && strcmp(fieldName, "linkCost") == 0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrLinkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_linkID
        "unsigned long",    // FIELD_linkData
        "inet::nlsr::LinkType",    // FIELD_type
        "unsigned long",    // FIELD_linkCost
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrLinkDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NlsrLinkDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_type:
            if (!strcmp(propertyname, "enum")) return "inet::nlsr::LinkType";
            return nullptr;
        default: return nullptr;
    }
}

int NlsrLinkDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrLink *pp = (NlsrLink *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrLinkDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLink *pp = (NlsrLink *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrLinkDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLink *pp = (NlsrLink *)object; (void)pp;
    switch (field) {
        case FIELD_linkID: {std::stringstream out; out << pp->getLinkID(); return out.str();}
        case FIELD_linkData: return ulong2string(pp->getLinkData());
        case FIELD_type: return enum2string(pp->getType(), "inet::nlsr::LinkType");
        case FIELD_linkCost: return ulong2string(pp->getLinkCost());
        default: return "";
    }
}

bool NlsrLinkDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrLink *pp = (NlsrLink *)object; (void)pp;
    switch (field) {
        case FIELD_linkData: pp->setLinkData(string2ulong(value)); return true;
        case FIELD_type: pp->setType((inet::nlsr::LinkType)string2enum(value, "inet::nlsr::LinkType")); return true;
        case FIELD_linkCost: pp->setLinkCost(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NlsrLinkDescriptor::getFieldStructName(int field) const
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

void *NlsrLinkDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrLink *pp = (NlsrLink *)object; (void)pp;
    switch (field) {
        case FIELD_linkID: return toVoidPtr(&pp->getLinkID()); break;
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::nlsr::NlsrLsaType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::nlsr::NlsrLsaType"));
    e->insert(ADJ_LSA, "ADJ_LSA");
    e->insert(COORD_LSA, "COORD_LSA");
    e->insert(NAME_LSA, "NAME_LSA");
)

Register_Class(NlsrLsaHeader)

NlsrLsaHeader::NlsrLsaHeader() : ::omnetpp::cObject()
{
}

NlsrLsaHeader::NlsrLsaHeader(const NlsrLsaHeader& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NlsrLsaHeader::~NlsrLsaHeader()
{
}

NlsrLsaHeader& NlsrLsaHeader::operator=(const NlsrLsaHeader& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NlsrLsaHeader::copy(const NlsrLsaHeader& other)
{
    this->interestName = other.interestName;
    this->originRouter = other.originRouter;
    this->lsAge = other.lsAge;
    this->lsType = other.lsType;
    this->hopCount = other.hopCount;
    this->seqNo = other.seqNo;
    this->hopLimit = other.hopLimit;
    this->lsaLength = other.lsaLength;
}

void NlsrLsaHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->interestName);
    doParsimPacking(b,this->originRouter);
    doParsimPacking(b,this->lsAge);
    doParsimPacking(b,this->lsType);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->lsaLength);
}

void NlsrLsaHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->interestName);
    doParsimUnpacking(b,this->originRouter);
    doParsimUnpacking(b,this->lsAge);
    doParsimUnpacking(b,this->lsType);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->lsaLength);
}

const iName& NlsrLsaHeader::getInterestName() const
{
    return this->interestName;
}

void NlsrLsaHeader::setInterestName(const iName& interestName)
{
    this->interestName = interestName;
}

const iName& NlsrLsaHeader::getOriginRouter() const
{
    return this->originRouter;
}

void NlsrLsaHeader::setOriginRouter(const iName& originRouter)
{
    this->originRouter = originRouter;
}

unsigned short NlsrLsaHeader::getLsAge() const
{
    return this->lsAge;
}

void NlsrLsaHeader::setLsAge(unsigned short lsAge)
{
    this->lsAge = lsAge;
}

inet::nlsr::NlsrLsaType NlsrLsaHeader::getLsType() const
{
    return this->lsType;
}

void NlsrLsaHeader::setLsType(inet::nlsr::NlsrLsaType lsType)
{
    this->lsType = lsType;
}

int NlsrLsaHeader::getHopCount() const
{
    return this->hopCount;
}

void NlsrLsaHeader::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

unsigned long NlsrLsaHeader::getSeqNo() const
{
    return this->seqNo;
}

void NlsrLsaHeader::setSeqNo(unsigned long seqNo)
{
    this->seqNo = seqNo;
}

unsigned int NlsrLsaHeader::getHopLimit() const
{
    return this->hopLimit;
}

void NlsrLsaHeader::setHopLimit(unsigned int hopLimit)
{
    this->hopLimit = hopLimit;
}

uint16_t NlsrLsaHeader::getLsaLength() const
{
    return this->lsaLength;
}

void NlsrLsaHeader::setLsaLength(uint16_t lsaLength)
{
    this->lsaLength = lsaLength;
}

class NlsrLsaHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interestName,
        FIELD_originRouter,
        FIELD_lsAge,
        FIELD_lsType,
        FIELD_hopCount,
        FIELD_seqNo,
        FIELD_hopLimit,
        FIELD_lsaLength,
    };
  public:
    NlsrLsaHeaderDescriptor();
    virtual ~NlsrLsaHeaderDescriptor();

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

Register_ClassDescriptor(NlsrLsaHeaderDescriptor)

NlsrLsaHeaderDescriptor::NlsrLsaHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrLsaHeader)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NlsrLsaHeaderDescriptor::~NlsrLsaHeaderDescriptor()
{
    delete[] propertynames;
}

bool NlsrLsaHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrLsaHeader *>(obj)!=nullptr;
}

const char **NlsrLsaHeaderDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrLsaHeaderDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrLsaHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount() : 8;
}

unsigned int NlsrLsaHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_interestName
        0,    // FIELD_originRouter
        FD_ISEDITABLE,    // FIELD_lsAge
        FD_ISEDITABLE,    // FIELD_lsType
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_lsaLength
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *NlsrLsaHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interestName",
        "originRouter",
        "lsAge",
        "lsType",
        "hopCount",
        "seqNo",
        "hopLimit",
        "lsaLength",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int NlsrLsaHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestName") == 0) return base+0;
    if (fieldName[0] == 'o' && strcmp(fieldName, "originRouter") == 0) return base+1;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsAge") == 0) return base+2;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsType") == 0) return base+3;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+5;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+6;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsaLength") == 0) return base+7;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrLsaHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::iName",    // FIELD_interestName
        "inet::iName",    // FIELD_originRouter
        "unsigned short",    // FIELD_lsAge
        "inet::nlsr::NlsrLsaType",    // FIELD_lsType
        "int",    // FIELD_hopCount
        "unsigned long",    // FIELD_seqNo
        "unsigned int",    // FIELD_hopLimit
        "uint16_t",    // FIELD_lsaLength
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrLsaHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NlsrLsaHeaderDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType:
            if (!strcmp(propertyname, "enum")) return "inet::nlsr::NlsrLsaType";
            return nullptr;
        default: return nullptr;
    }
}

int NlsrLsaHeaderDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaHeader *pp = (NlsrLsaHeader *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrLsaHeaderDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaHeader *pp = (NlsrLsaHeader *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrLsaHeaderDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaHeader *pp = (NlsrLsaHeader *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: {std::stringstream out; out << pp->getInterestName(); return out.str();}
        case FIELD_originRouter: {std::stringstream out; out << pp->getOriginRouter(); return out.str();}
        case FIELD_lsAge: return ulong2string(pp->getLsAge());
        case FIELD_lsType: return enum2string(pp->getLsType(), "inet::nlsr::NlsrLsaType");
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_seqNo: return ulong2string(pp->getSeqNo());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        case FIELD_lsaLength: return ulong2string(pp->getLsaLength());
        default: return "";
    }
}

bool NlsrLsaHeaderDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaHeader *pp = (NlsrLsaHeader *)object; (void)pp;
    switch (field) {
        case FIELD_lsAge: pp->setLsAge(string2ulong(value)); return true;
        case FIELD_lsType: pp->setLsType((inet::nlsr::NlsrLsaType)string2enum(value, "inet::nlsr::NlsrLsaType")); return true;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2ulong(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        case FIELD_lsaLength: pp->setLsaLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NlsrLsaHeaderDescriptor::getFieldStructName(int field) const
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

void *NlsrLsaHeaderDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaHeader *pp = (NlsrLsaHeader *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: return toVoidPtr(&pp->getInterestName()); break;
        case FIELD_originRouter: return toVoidPtr(&pp->getOriginRouter()); break;
        default: return nullptr;
    }
}

Register_Class(NlsrLsa)

NlsrLsa::NlsrLsa() : ::omnetpp::cObject()
{
}

NlsrLsa::NlsrLsa(const NlsrLsa& other) : ::omnetpp::cObject(other)
{
    copy(other);
}

NlsrLsa::~NlsrLsa()
{
}

NlsrLsa& NlsrLsa::operator=(const NlsrLsa& other)
{
    if (this == &other) return *this;
    ::omnetpp::cObject::operator=(other);
    copy(other);
    return *this;
}

void NlsrLsa::copy(const NlsrLsa& other)
{
    this->header = other.header;
}

void NlsrLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    doParsimPacking(b,this->header);
}

void NlsrLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    doParsimUnpacking(b,this->header);
}

const NlsrLsaHeader& NlsrLsa::getHeader() const
{
    return this->header;
}

void NlsrLsa::setHeader(const NlsrLsaHeader& header)
{
    this->header = header;
}

class NlsrLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_header,
    };
  public:
    NlsrLsaDescriptor();
    virtual ~NlsrLsaDescriptor();

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

Register_ClassDescriptor(NlsrLsaDescriptor)

NlsrLsaDescriptor::NlsrLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrLsa)), "omnetpp::cObject")
{
    propertynames = nullptr;
}

NlsrLsaDescriptor::~NlsrLsaDescriptor()
{
    delete[] propertynames;
}

bool NlsrLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrLsa *>(obj)!=nullptr;
}

const char **NlsrLsaDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrLsaDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int NlsrLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_header
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *NlsrLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "header",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int NlsrLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "header") == 0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrLsaHeader",    // FIELD_header
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrLsaDescriptor::getFieldPropertyNames(int field) const
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

const char *NlsrLsaDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NlsrLsaDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrLsa *pp = (NlsrLsa *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrLsaDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsa *pp = (NlsrLsa *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrLsaDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsa *pp = (NlsrLsa *)object; (void)pp;
    switch (field) {
        case FIELD_header: {std::stringstream out; out << pp->getHeader(); return out.str();}
        default: return "";
    }
}

bool NlsrLsaDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrLsa *pp = (NlsrLsa *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *NlsrLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_header: return omnetpp::opp_typename(typeid(NlsrLsaHeader));
        default: return nullptr;
    };
}

void *NlsrLsaDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsa *pp = (NlsrLsa *)object; (void)pp;
    switch (field) {
        case FIELD_header: return toVoidPtr(&pp->getHeader()); break;
        default: return nullptr;
    }
}

Register_Class(NlsrAdjLsa)

NlsrAdjLsa::NlsrAdjLsa() : ::inet::nlsr::NlsrLsa()
{
}

NlsrAdjLsa::NlsrAdjLsa(const NlsrAdjLsa& other) : ::inet::nlsr::NlsrLsa(other)
{
    copy(other);
}

NlsrAdjLsa::~NlsrAdjLsa()
{
}

NlsrAdjLsa& NlsrAdjLsa::operator=(const NlsrAdjLsa& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrLsa::operator=(other);
    copy(other);
    return *this;
}

void NlsrAdjLsa::copy(const NlsrAdjLsa& other)
{
    this->lsType = other.lsType;
    this->m_adl = other.m_adl;
}

void NlsrAdjLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrLsa::parsimPack(b);
    doParsimPacking(b,this->lsType);
    doParsimPacking(b,this->m_adl);
}

void NlsrAdjLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrLsa::parsimUnpack(b);
    doParsimUnpacking(b,this->lsType);
    doParsimUnpacking(b,this->m_adl);
}

inet::nlsr::NlsrLsaType NlsrAdjLsa::getLsType() const
{
    return this->lsType;
}

void NlsrAdjLsa::setLsType(inet::nlsr::NlsrLsaType lsType)
{
    this->lsType = lsType;
}

const inet::nlsr::AdjacencyList * NlsrAdjLsa::getM_adl() const
{
    return this->m_adl;
}

void NlsrAdjLsa::setM_adl(inet::nlsr::AdjacencyList * m_adl)
{
    this->m_adl = m_adl;
}

class NlsrAdjLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_lsType,
        FIELD_m_adl,
    };
  public:
    NlsrAdjLsaDescriptor();
    virtual ~NlsrAdjLsaDescriptor();

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

Register_ClassDescriptor(NlsrAdjLsaDescriptor)

NlsrAdjLsaDescriptor::NlsrAdjLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrAdjLsa)), "inet::nlsr::NlsrLsa")
{
    propertynames = nullptr;
}

NlsrAdjLsaDescriptor::~NlsrAdjLsaDescriptor()
{
    delete[] propertynames;
}

bool NlsrAdjLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrAdjLsa *>(obj)!=nullptr;
}

const char **NlsrAdjLsaDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrAdjLsaDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrAdjLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NlsrAdjLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsType
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_m_adl
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NlsrAdjLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsType",
        "m_adl",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NlsrAdjLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsType") == 0) return base+0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "m_adl") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrAdjLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrLsaType",    // FIELD_lsType
        "inet::nlsr::AdjacencyList",    // FIELD_m_adl
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrAdjLsaDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NlsrAdjLsaDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType:
            if (!strcmp(propertyname, "enum")) return "inet::nlsr::NlsrLsaType";
            return nullptr;
        default: return nullptr;
    }
}

int NlsrAdjLsaDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrAdjLsa *pp = (NlsrAdjLsa *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrAdjLsaDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrAdjLsa *pp = (NlsrAdjLsa *)object; (void)pp;
    switch (field) {
        case FIELD_m_adl: { const inet::nlsr::AdjacencyList * value = pp->getM_adl(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string NlsrAdjLsaDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrAdjLsa *pp = (NlsrAdjLsa *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: return enum2string(pp->getLsType(), "inet::nlsr::NlsrLsaType");
        case FIELD_m_adl: {std::stringstream out; out << pp->getM_adl(); return out.str();}
        default: return "";
    }
}

bool NlsrAdjLsaDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrAdjLsa *pp = (NlsrAdjLsa *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: pp->setLsType((inet::nlsr::NlsrLsaType)string2enum(value, "inet::nlsr::NlsrLsaType")); return true;
        default: return false;
    }
}

const char *NlsrAdjLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_m_adl: return omnetpp::opp_typename(typeid(inet::nlsr::AdjacencyList));
        default: return nullptr;
    };
}

void *NlsrAdjLsaDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrAdjLsa *pp = (NlsrAdjLsa *)object; (void)pp;
    switch (field) {
        case FIELD_m_adl: return toVoidPtr(pp->getM_adl()); break;
        default: return nullptr;
    }
}

Register_Class(NlsrNameLsa)

NlsrNameLsa::NlsrNameLsa() : ::inet::nlsr::NlsrLsa()
{
}

NlsrNameLsa::NlsrNameLsa(const NlsrNameLsa& other) : ::inet::nlsr::NlsrLsa(other)
{
    copy(other);
}

NlsrNameLsa::~NlsrNameLsa()
{
}

NlsrNameLsa& NlsrNameLsa::operator=(const NlsrNameLsa& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrLsa::operator=(other);
    copy(other);
    return *this;
}

void NlsrNameLsa::copy(const NlsrNameLsa& other)
{
    this->lsType = other.lsType;
    this->m_npl = other.m_npl;
}

void NlsrNameLsa::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrLsa::parsimPack(b);
    doParsimPacking(b,this->lsType);
    doParsimPacking(b,this->m_npl);
}

void NlsrNameLsa::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrLsa::parsimUnpack(b);
    doParsimUnpacking(b,this->lsType);
    doParsimUnpacking(b,this->m_npl);
}

inet::nlsr::NlsrLsaType NlsrNameLsa::getLsType() const
{
    return this->lsType;
}

void NlsrNameLsa::setLsType(inet::nlsr::NlsrLsaType lsType)
{
    this->lsType = lsType;
}

const inet::nlsr::NamePrefixList * NlsrNameLsa::getM_npl() const
{
    return this->m_npl;
}

void NlsrNameLsa::setM_npl(inet::nlsr::NamePrefixList * m_npl)
{
    this->m_npl = m_npl;
}

class NlsrNameLsaDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_lsType,
        FIELD_m_npl,
    };
  public:
    NlsrNameLsaDescriptor();
    virtual ~NlsrNameLsaDescriptor();

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

Register_ClassDescriptor(NlsrNameLsaDescriptor)

NlsrNameLsaDescriptor::NlsrNameLsaDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrNameLsa)), "inet::nlsr::NlsrLsa")
{
    propertynames = nullptr;
}

NlsrNameLsaDescriptor::~NlsrNameLsaDescriptor()
{
    delete[] propertynames;
}

bool NlsrNameLsaDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrNameLsa *>(obj)!=nullptr;
}

const char **NlsrNameLsaDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrNameLsaDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrNameLsaDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NlsrNameLsaDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsType
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_m_npl
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NlsrNameLsaDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsType",
        "m_npl",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NlsrNameLsaDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsType") == 0) return base+0;
    if (fieldName[0] == 'm' && strcmp(fieldName, "m_npl") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrNameLsaDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrLsaType",    // FIELD_lsType
        "inet::nlsr::NamePrefixList",    // FIELD_m_npl
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrNameLsaDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NlsrNameLsaDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_lsType:
            if (!strcmp(propertyname, "enum")) return "inet::nlsr::NlsrLsaType";
            return nullptr;
        default: return nullptr;
    }
}

int NlsrNameLsaDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrNameLsa *pp = (NlsrNameLsa *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrNameLsaDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrNameLsa *pp = (NlsrNameLsa *)object; (void)pp;
    switch (field) {
        case FIELD_m_npl: { const inet::nlsr::NamePrefixList * value = pp->getM_npl(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string NlsrNameLsaDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrNameLsa *pp = (NlsrNameLsa *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: return enum2string(pp->getLsType(), "inet::nlsr::NlsrLsaType");
        case FIELD_m_npl: {std::stringstream out; out << pp->getM_npl(); return out.str();}
        default: return "";
    }
}

bool NlsrNameLsaDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrNameLsa *pp = (NlsrNameLsa *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: pp->setLsType((inet::nlsr::NlsrLsaType)string2enum(value, "inet::nlsr::NlsrLsaType")); return true;
        default: return false;
    }
}

const char *NlsrNameLsaDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_m_npl: return omnetpp::opp_typename(typeid(inet::nlsr::NamePrefixList));
        default: return nullptr;
    };
}

void *NlsrNameLsaDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrNameLsa *pp = (NlsrNameLsa *)object; (void)pp;
    switch (field) {
        case FIELD_m_npl: return toVoidPtr(pp->getM_npl()); break;
        default: return nullptr;
    }
}

NlsrLsaInterest::NlsrLsaInterest()
{
    this->lsType = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const NlsrLsaInterest& a)
{
    doParsimPacking(b,a.lsType);
    doParsimPacking(b,a.interestName);
}

void __doUnpacking(omnetpp::cCommBuffer *b, NlsrLsaInterest& a)
{
    doParsimUnpacking(b,a.lsType);
    doParsimUnpacking(b,a.interestName);
}

class NlsrLsaInterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_lsType,
        FIELD_interestName,
    };
  public:
    NlsrLsaInterestDescriptor();
    virtual ~NlsrLsaInterestDescriptor();

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

Register_ClassDescriptor(NlsrLsaInterestDescriptor)

NlsrLsaInterestDescriptor::NlsrLsaInterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NlsrLsaInterest)), "")
{
    propertynames = nullptr;
}

NlsrLsaInterestDescriptor::~NlsrLsaInterestDescriptor()
{
    delete[] propertynames;
}

bool NlsrLsaInterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NlsrLsaInterest *>(obj)!=nullptr;
}

const char **NlsrLsaInterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NlsrLsaInterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NlsrLsaInterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount() : 2;
}

unsigned int NlsrLsaInterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_lsType
        0,    // FIELD_interestName
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *NlsrLsaInterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "lsType",
        "interestName",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int NlsrLsaInterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'l' && strcmp(fieldName, "lsType") == 0) return base+0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestName") == 0) return base+1;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NlsrLsaInterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",    // FIELD_lsType
        "inet::iName",    // FIELD_interestName
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **NlsrLsaInterestDescriptor::getFieldPropertyNames(int field) const
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

const char *NlsrLsaInterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NlsrLsaInterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaInterest *pp = (NlsrLsaInterest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NlsrLsaInterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaInterest *pp = (NlsrLsaInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NlsrLsaInterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaInterest *pp = (NlsrLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: return ulong2string(pp->lsType);
        case FIELD_interestName: {std::stringstream out; out << pp->interestName; return out.str();}
        default: return "";
    }
}

bool NlsrLsaInterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaInterest *pp = (NlsrLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_lsType: pp->lsType = string2ulong(value); return true;
        default: return false;
    }
}

const char *NlsrLsaInterestDescriptor::getFieldStructName(int field) const
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

void *NlsrLsaInterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NlsrLsaInterest *pp = (NlsrLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interestName: return toVoidPtr(&pp->interestName); break;
        default: return nullptr;
    }
}

Register_Class(AdjLsaInterest)

AdjLsaInterest::AdjLsaInterest() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1000));

}

AdjLsaInterest::AdjLsaInterest(const AdjLsaInterest& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

AdjLsaInterest::~AdjLsaInterest()
{
    delete [] this->interests;
}

AdjLsaInterest& AdjLsaInterest::operator=(const AdjLsaInterest& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void AdjLsaInterest::copy(const AdjLsaInterest& other)
{
    delete [] this->interests;
    this->interests = (other.interests_arraysize==0) ? nullptr : new NlsrLsaInterest[other.interests_arraysize];
    interests_arraysize = other.interests_arraysize;
    for (size_t i = 0; i < interests_arraysize; i++) {
        this->interests[i] = other.interests[i];
    }
    this->hopCount = other.hopCount;
    this->hopLimit = other.hopLimit;
    this->seqNo = other.seqNo;
    this->canBePrefix = other.canBePrefix;
    this->MustBeFresh = other.MustBeFresh;
    this->interestLifetimeMs = other.interestLifetimeMs;
}

void AdjLsaInterest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    b->pack(interests_arraysize);
    doParsimArrayPacking(b,this->interests,interests_arraysize);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->canBePrefix);
    doParsimPacking(b,this->MustBeFresh);
    doParsimPacking(b,this->interestLifetimeMs);
}

void AdjLsaInterest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    delete [] this->interests;
    b->unpack(interests_arraysize);
    if (interests_arraysize == 0) {
        this->interests = nullptr;
    } else {
        this->interests = new NlsrLsaInterest[interests_arraysize];
        doParsimArrayUnpacking(b,this->interests,interests_arraysize);
    }
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->canBePrefix);
    doParsimUnpacking(b,this->MustBeFresh);
    doParsimUnpacking(b,this->interestLifetimeMs);
}

size_t AdjLsaInterest::getInterestsArraySize() const
{
    return interests_arraysize;
}

const NlsrLsaInterest& AdjLsaInterest::getInterests(size_t k) const
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size interests_arraysize indexed by %lu", (unsigned long)k);
    return this->interests[k];
}

void AdjLsaInterest::setInterestsArraySize(size_t newSize)
{
    handleChange();
    NlsrLsaInterest *interests2 = (newSize==0) ? nullptr : new NlsrLsaInterest[newSize];
    size_t minSize = interests_arraysize < newSize ? interests_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        interests2[i] = this->interests[i];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

void AdjLsaInterest::setInterests(size_t k, const NlsrLsaInterest& interests)
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->interests[k] = interests;
}

void AdjLsaInterest::insertInterests(size_t k, const NlsrLsaInterest& interests)
{
    handleChange();
    if (k > interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = interests_arraysize + 1;
    NlsrLsaInterest *interests2 = new NlsrLsaInterest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interests2[i] = this->interests[i];
    interests2[k] = interests;
    for (i = k + 1; i < newSize; i++)
        interests2[i] = this->interests[i-1];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

void AdjLsaInterest::insertInterests(const NlsrLsaInterest& interests)
{
    insertInterests(interests_arraysize, interests);
}

void AdjLsaInterest::eraseInterests(size_t k)
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = interests_arraysize - 1;
    NlsrLsaInterest *interests2 = (newSize == 0) ? nullptr : new NlsrLsaInterest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interests2[i] = this->interests[i];
    for (i = k; i < newSize; i++)
        interests2[i] = this->interests[i+1];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

int AdjLsaInterest::getHopCount() const
{
    return this->hopCount;
}

void AdjLsaInterest::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int AdjLsaInterest::getHopLimit() const
{
    return this->hopLimit;
}

void AdjLsaInterest::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

long AdjLsaInterest::getSeqNo() const
{
    return this->seqNo;
}

void AdjLsaInterest::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

bool AdjLsaInterest::getCanBePrefix() const
{
    return this->canBePrefix;
}

void AdjLsaInterest::setCanBePrefix(bool canBePrefix)
{
    handleChange();
    this->canBePrefix = canBePrefix;
}

bool AdjLsaInterest::getMustBeFresh() const
{
    return this->MustBeFresh;
}

void AdjLsaInterest::setMustBeFresh(bool MustBeFresh)
{
    handleChange();
    this->MustBeFresh = MustBeFresh;
}

unsigned int AdjLsaInterest::getInterestLifetimeMs() const
{
    return this->interestLifetimeMs;
}

void AdjLsaInterest::setInterestLifetimeMs(unsigned int interestLifetimeMs)
{
    handleChange();
    this->interestLifetimeMs = interestLifetimeMs;
}

class AdjLsaInterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interests,
        FIELD_hopCount,
        FIELD_hopLimit,
        FIELD_seqNo,
        FIELD_canBePrefix,
        FIELD_MustBeFresh,
        FIELD_interestLifetimeMs,
    };
  public:
    AdjLsaInterestDescriptor();
    virtual ~AdjLsaInterestDescriptor();

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

Register_ClassDescriptor(AdjLsaInterestDescriptor)

AdjLsaInterestDescriptor::AdjLsaInterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::AdjLsaInterest)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

AdjLsaInterestDescriptor::~AdjLsaInterestDescriptor()
{
    delete[] propertynames;
}

bool AdjLsaInterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AdjLsaInterest *>(obj)!=nullptr;
}

const char **AdjLsaInterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AdjLsaInterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AdjLsaInterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int AdjLsaInterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,    // FIELD_interests
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_canBePrefix
        FD_ISEDITABLE,    // FIELD_MustBeFresh
        FD_ISEDITABLE,    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *AdjLsaInterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interests",
        "hopCount",
        "hopLimit",
        "seqNo",
        "canBePrefix",
        "MustBeFresh",
        "interestLifetimeMs",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int AdjLsaInterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interests") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "canBePrefix") == 0) return base+4;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MustBeFresh") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestLifetimeMs") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AdjLsaInterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrLsaInterest",    // FIELD_interests
        "int",    // FIELD_hopCount
        "unsigned int",    // FIELD_hopLimit
        "long",    // FIELD_seqNo
        "bool",    // FIELD_canBePrefix
        "bool",    // FIELD_MustBeFresh
        "unsigned int",    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **AdjLsaInterestDescriptor::getFieldPropertyNames(int field) const
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

const char *AdjLsaInterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int AdjLsaInterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AdjLsaInterest *pp = (AdjLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: return pp->getInterestsArraySize();
        default: return 0;
    }
}

const char *AdjLsaInterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AdjLsaInterest *pp = (AdjLsaInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AdjLsaInterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AdjLsaInterest *pp = (AdjLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: {std::stringstream out; out << pp->getInterests(i); return out.str();}
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_canBePrefix: return bool2string(pp->getCanBePrefix());
        case FIELD_MustBeFresh: return bool2string(pp->getMustBeFresh());
        case FIELD_interestLifetimeMs: return ulong2string(pp->getInterestLifetimeMs());
        default: return "";
    }
}

bool AdjLsaInterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AdjLsaInterest *pp = (AdjLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_canBePrefix: pp->setCanBePrefix(string2bool(value)); return true;
        case FIELD_MustBeFresh: pp->setMustBeFresh(string2bool(value)); return true;
        case FIELD_interestLifetimeMs: pp->setInterestLifetimeMs(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AdjLsaInterestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_interests: return omnetpp::opp_typename(typeid(NlsrLsaInterest));
        default: return nullptr;
    };
}

void *AdjLsaInterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AdjLsaInterest *pp = (AdjLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: return toVoidPtr(&pp->getInterests(i)); break;
        default: return nullptr;
    }
}

Register_Class(NameLsaInterest)

NameLsaInterest::NameLsaInterest() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1000));

}

NameLsaInterest::NameLsaInterest(const NameLsaInterest& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

NameLsaInterest::~NameLsaInterest()
{
    delete [] this->interests;
}

NameLsaInterest& NameLsaInterest::operator=(const NameLsaInterest& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void NameLsaInterest::copy(const NameLsaInterest& other)
{
    delete [] this->interests;
    this->interests = (other.interests_arraysize==0) ? nullptr : new NlsrLsaInterest[other.interests_arraysize];
    interests_arraysize = other.interests_arraysize;
    for (size_t i = 0; i < interests_arraysize; i++) {
        this->interests[i] = other.interests[i];
    }
    this->hopCount = other.hopCount;
    this->hopLimit = other.hopLimit;
    this->seqNo = other.seqNo;
    this->canBePrefix = other.canBePrefix;
    this->MustBeFresh = other.MustBeFresh;
    this->interestLifetimeMs = other.interestLifetimeMs;
}

void NameLsaInterest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    b->pack(interests_arraysize);
    doParsimArrayPacking(b,this->interests,interests_arraysize);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->hopLimit);
    doParsimPacking(b,this->seqNo);
    doParsimPacking(b,this->canBePrefix);
    doParsimPacking(b,this->MustBeFresh);
    doParsimPacking(b,this->interestLifetimeMs);
}

void NameLsaInterest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    delete [] this->interests;
    b->unpack(interests_arraysize);
    if (interests_arraysize == 0) {
        this->interests = nullptr;
    } else {
        this->interests = new NlsrLsaInterest[interests_arraysize];
        doParsimArrayUnpacking(b,this->interests,interests_arraysize);
    }
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->hopLimit);
    doParsimUnpacking(b,this->seqNo);
    doParsimUnpacking(b,this->canBePrefix);
    doParsimUnpacking(b,this->MustBeFresh);
    doParsimUnpacking(b,this->interestLifetimeMs);
}

size_t NameLsaInterest::getInterestsArraySize() const
{
    return interests_arraysize;
}

const NlsrLsaInterest& NameLsaInterest::getInterests(size_t k) const
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size interests_arraysize indexed by %lu", (unsigned long)k);
    return this->interests[k];
}

void NameLsaInterest::setInterestsArraySize(size_t newSize)
{
    handleChange();
    NlsrLsaInterest *interests2 = (newSize==0) ? nullptr : new NlsrLsaInterest[newSize];
    size_t minSize = interests_arraysize < newSize ? interests_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        interests2[i] = this->interests[i];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

void NameLsaInterest::setInterests(size_t k, const NlsrLsaInterest& interests)
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    this->interests[k] = interests;
}

void NameLsaInterest::insertInterests(size_t k, const NlsrLsaInterest& interests)
{
    handleChange();
    if (k > interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    size_t newSize = interests_arraysize + 1;
    NlsrLsaInterest *interests2 = new NlsrLsaInterest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interests2[i] = this->interests[i];
    interests2[k] = interests;
    for (i = k + 1; i < newSize; i++)
        interests2[i] = this->interests[i-1];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

void NameLsaInterest::insertInterests(const NlsrLsaInterest& interests)
{
    insertInterests(interests_arraysize, interests);
}

void NameLsaInterest::eraseInterests(size_t k)
{
    if (k >= interests_arraysize) throw omnetpp::cRuntimeError("Array of size  indexed by %lu", (unsigned long)k);
    handleChange();
    size_t newSize = interests_arraysize - 1;
    NlsrLsaInterest *interests2 = (newSize == 0) ? nullptr : new NlsrLsaInterest[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        interests2[i] = this->interests[i];
    for (i = k; i < newSize; i++)
        interests2[i] = this->interests[i+1];
    delete [] this->interests;
    this->interests = interests2;
    interests_arraysize = newSize;
}

int NameLsaInterest::getHopCount() const
{
    return this->hopCount;
}

void NameLsaInterest::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int NameLsaInterest::getHopLimit() const
{
    return this->hopLimit;
}

void NameLsaInterest::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

long NameLsaInterest::getSeqNo() const
{
    return this->seqNo;
}

void NameLsaInterest::setSeqNo(long seqNo)
{
    handleChange();
    this->seqNo = seqNo;
}

bool NameLsaInterest::getCanBePrefix() const
{
    return this->canBePrefix;
}

void NameLsaInterest::setCanBePrefix(bool canBePrefix)
{
    handleChange();
    this->canBePrefix = canBePrefix;
}

bool NameLsaInterest::getMustBeFresh() const
{
    return this->MustBeFresh;
}

void NameLsaInterest::setMustBeFresh(bool MustBeFresh)
{
    handleChange();
    this->MustBeFresh = MustBeFresh;
}

unsigned int NameLsaInterest::getInterestLifetimeMs() const
{
    return this->interestLifetimeMs;
}

void NameLsaInterest::setInterestLifetimeMs(unsigned int interestLifetimeMs)
{
    handleChange();
    this->interestLifetimeMs = interestLifetimeMs;
}

class NameLsaInterestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_interests,
        FIELD_hopCount,
        FIELD_hopLimit,
        FIELD_seqNo,
        FIELD_canBePrefix,
        FIELD_MustBeFresh,
        FIELD_interestLifetimeMs,
    };
  public:
    NameLsaInterestDescriptor();
    virtual ~NameLsaInterestDescriptor();

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

Register_ClassDescriptor(NameLsaInterestDescriptor)

NameLsaInterestDescriptor::NameLsaInterestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NameLsaInterest)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

NameLsaInterestDescriptor::~NameLsaInterestDescriptor()
{
    delete[] propertynames;
}

bool NameLsaInterestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NameLsaInterest *>(obj)!=nullptr;
}

const char **NameLsaInterestDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NameLsaInterestDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NameLsaInterestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int NameLsaInterestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,    // FIELD_interests
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_hopLimit
        FD_ISEDITABLE,    // FIELD_seqNo
        FD_ISEDITABLE,    // FIELD_canBePrefix
        FD_ISEDITABLE,    // FIELD_MustBeFresh
        FD_ISEDITABLE,    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *NameLsaInterestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "interests",
        "hopCount",
        "hopLimit",
        "seqNo",
        "canBePrefix",
        "MustBeFresh",
        "interestLifetimeMs",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int NameLsaInterestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interests") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+2;
    if (fieldName[0] == 's' && strcmp(fieldName, "seqNo") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "canBePrefix") == 0) return base+4;
    if (fieldName[0] == 'M' && strcmp(fieldName, "MustBeFresh") == 0) return base+5;
    if (fieldName[0] == 'i' && strcmp(fieldName, "interestLifetimeMs") == 0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NameLsaInterestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrLsaInterest",    // FIELD_interests
        "int",    // FIELD_hopCount
        "unsigned int",    // FIELD_hopLimit
        "long",    // FIELD_seqNo
        "bool",    // FIELD_canBePrefix
        "bool",    // FIELD_MustBeFresh
        "unsigned int",    // FIELD_interestLifetimeMs
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **NameLsaInterestDescriptor::getFieldPropertyNames(int field) const
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

const char *NameLsaInterestDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NameLsaInterestDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NameLsaInterest *pp = (NameLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: return pp->getInterestsArraySize();
        default: return 0;
    }
}

const char *NameLsaInterestDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NameLsaInterest *pp = (NameLsaInterest *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NameLsaInterestDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NameLsaInterest *pp = (NameLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: {std::stringstream out; out << pp->getInterests(i); return out.str();}
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        case FIELD_seqNo: return long2string(pp->getSeqNo());
        case FIELD_canBePrefix: return bool2string(pp->getCanBePrefix());
        case FIELD_MustBeFresh: return bool2string(pp->getMustBeFresh());
        case FIELD_interestLifetimeMs: return ulong2string(pp->getInterestLifetimeMs());
        default: return "";
    }
}

bool NameLsaInterestDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NameLsaInterest *pp = (NameLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        case FIELD_seqNo: pp->setSeqNo(string2long(value)); return true;
        case FIELD_canBePrefix: pp->setCanBePrefix(string2bool(value)); return true;
        case FIELD_MustBeFresh: pp->setMustBeFresh(string2bool(value)); return true;
        case FIELD_interestLifetimeMs: pp->setInterestLifetimeMs(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NameLsaInterestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_interests: return omnetpp::opp_typename(typeid(NlsrLsaInterest));
        default: return nullptr;
    };
}

void *NameLsaInterestDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NameLsaInterest *pp = (NameLsaInterest *)object; (void)pp;
    switch (field) {
        case FIELD_interests: return toVoidPtr(&pp->getInterests(i)); break;
        default: return nullptr;
    }
}

Register_Class(AdjDataPacket)

AdjDataPacket::AdjDataPacket() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1000));

}

AdjDataPacket::AdjDataPacket(const AdjDataPacket& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

AdjDataPacket::~AdjDataPacket()
{
}

AdjDataPacket& AdjDataPacket::operator=(const AdjDataPacket& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void AdjDataPacket::copy(const AdjDataPacket& other)
{
    this->adjLSA = other.adjLSA;
    this->hopCount = other.hopCount;
    this->hopLimit = other.hopLimit;
}

void AdjDataPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->adjLSA);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->hopLimit);
}

void AdjDataPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->adjLSA);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->hopLimit);
}

const NlsrAdjLsa * AdjDataPacket::getAdjLSA() const
{
    return this->adjLSA;
}

void AdjDataPacket::setAdjLSA(NlsrAdjLsa * adjLSA)
{
    handleChange();
    this->adjLSA = adjLSA;
}

int AdjDataPacket::getHopCount() const
{
    return this->hopCount;
}

void AdjDataPacket::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int AdjDataPacket::getHopLimit() const
{
    return this->hopLimit;
}

void AdjDataPacket::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

class AdjDataPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_adjLSA,
        FIELD_hopCount,
        FIELD_hopLimit,
    };
  public:
    AdjDataPacketDescriptor();
    virtual ~AdjDataPacketDescriptor();

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

Register_ClassDescriptor(AdjDataPacketDescriptor)

AdjDataPacketDescriptor::AdjDataPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::AdjDataPacket)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

AdjDataPacketDescriptor::~AdjDataPacketDescriptor()
{
    delete[] propertynames;
}

bool AdjDataPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AdjDataPacket *>(obj)!=nullptr;
}

const char **AdjDataPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *AdjDataPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int AdjDataPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int AdjDataPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_adjLSA
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_hopLimit
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *AdjDataPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "adjLSA",
        "hopCount",
        "hopLimit",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int AdjDataPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'a' && strcmp(fieldName, "adjLSA") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *AdjDataPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrAdjLsa",    // FIELD_adjLSA
        "int",    // FIELD_hopCount
        "unsigned int",    // FIELD_hopLimit
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **AdjDataPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *AdjDataPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int AdjDataPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    AdjDataPacket *pp = (AdjDataPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *AdjDataPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AdjDataPacket *pp = (AdjDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_adjLSA: { const NlsrAdjLsa * value = pp->getAdjLSA(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string AdjDataPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    AdjDataPacket *pp = (AdjDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_adjLSA: {std::stringstream out; out << pp->getAdjLSA(); return out.str();}
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        default: return "";
    }
}

bool AdjDataPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    AdjDataPacket *pp = (AdjDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AdjDataPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_adjLSA: return omnetpp::opp_typename(typeid(NlsrAdjLsa));
        default: return nullptr;
    };
}

void *AdjDataPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    AdjDataPacket *pp = (AdjDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_adjLSA: return toVoidPtr(pp->getAdjLSA()); break;
        default: return nullptr;
    }
}

Register_Class(NameDataPacket)

NameDataPacket::NameDataPacket() : ::inet::nlsr::NlsrPacket()
{
    this->setChunkLength(B(1000));

}

NameDataPacket::NameDataPacket(const NameDataPacket& other) : ::inet::nlsr::NlsrPacket(other)
{
    copy(other);
}

NameDataPacket::~NameDataPacket()
{
}

NameDataPacket& NameDataPacket::operator=(const NameDataPacket& other)
{
    if (this == &other) return *this;
    ::inet::nlsr::NlsrPacket::operator=(other);
    copy(other);
    return *this;
}

void NameDataPacket::copy(const NameDataPacket& other)
{
    this->nameLSA = other.nameLSA;
    this->hopCount = other.hopCount;
    this->hopLimit = other.hopLimit;
}

void NameDataPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::nlsr::NlsrPacket::parsimPack(b);
    doParsimPacking(b,this->nameLSA);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->hopLimit);
}

void NameDataPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::nlsr::NlsrPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->nameLSA);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->hopLimit);
}

const NlsrNameLsa * NameDataPacket::getNameLSA() const
{
    return this->nameLSA;
}

void NameDataPacket::setNameLSA(NlsrNameLsa * nameLSA)
{
    handleChange();
    this->nameLSA = nameLSA;
}

int NameDataPacket::getHopCount() const
{
    return this->hopCount;
}

void NameDataPacket::setHopCount(int hopCount)
{
    handleChange();
    this->hopCount = hopCount;
}

unsigned int NameDataPacket::getHopLimit() const
{
    return this->hopLimit;
}

void NameDataPacket::setHopLimit(unsigned int hopLimit)
{
    handleChange();
    this->hopLimit = hopLimit;
}

class NameDataPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_nameLSA,
        FIELD_hopCount,
        FIELD_hopLimit,
    };
  public:
    NameDataPacketDescriptor();
    virtual ~NameDataPacketDescriptor();

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

Register_ClassDescriptor(NameDataPacketDescriptor)

NameDataPacketDescriptor::NameDataPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::nlsr::NameDataPacket)), "inet::nlsr::NlsrPacket")
{
    propertynames = nullptr;
}

NameDataPacketDescriptor::~NameDataPacketDescriptor()
{
    delete[] propertynames;
}

bool NameDataPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NameDataPacket *>(obj)!=nullptr;
}

const char **NameDataPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *NameDataPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int NameDataPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int NameDataPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_nameLSA
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_hopLimit
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *NameDataPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nameLSA",
        "hopCount",
        "hopLimit",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int NameDataPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'n' && strcmp(fieldName, "nameLSA") == 0) return base+0;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopCount") == 0) return base+1;
    if (fieldName[0] == 'h' && strcmp(fieldName, "hopLimit") == 0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *NameDataPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::nlsr::NlsrNameLsa",    // FIELD_nameLSA
        "int",    // FIELD_hopCount
        "unsigned int",    // FIELD_hopLimit
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **NameDataPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *NameDataPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int NameDataPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    NameDataPacket *pp = (NameDataPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *NameDataPacketDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NameDataPacket *pp = (NameDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_nameLSA: { const NlsrNameLsa * value = pp->getNameLSA(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string NameDataPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    NameDataPacket *pp = (NameDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_nameLSA: {std::stringstream out; out << pp->getNameLSA(); return out.str();}
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_hopLimit: return ulong2string(pp->getHopLimit());
        default: return "";
    }
}

bool NameDataPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    NameDataPacket *pp = (NameDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_hopCount: pp->setHopCount(string2long(value)); return true;
        case FIELD_hopLimit: pp->setHopLimit(string2ulong(value)); return true;
        default: return false;
    }
}

const char *NameDataPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_nameLSA: return omnetpp::opp_typename(typeid(NlsrNameLsa));
        default: return nullptr;
    };
}

void *NameDataPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    NameDataPacket *pp = (NameDataPacket *)object; (void)pp;
    switch (field) {
        case FIELD_nameLSA: return toVoidPtr(pp->getNameLSA()); break;
        default: return nullptr;
    }
}

} // namespace nlsr
} // namespace inet

