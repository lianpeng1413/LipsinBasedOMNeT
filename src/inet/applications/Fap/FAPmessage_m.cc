//
// Generated file, do not edit! Created by nedtool 5.6 from inet/applications/Fap/FAPmessage.msg.
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
#include "FAPmessage_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("inet::FAPmsgType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("inet::FAPmsgType"));
    e->insert(HELLO, "HELLO");
    e->insert(AREQ, "AREQ");
    e->insert(AF, "AF");
    e->insert(PARTITION, "PARTITION");
)

Register_Class(FAPhead)

FAPhead::FAPhead() : ::inet::FieldsChunk()
{
}

FAPhead::FAPhead(const FAPhead& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

FAPhead::~FAPhead()
{
}

FAPhead& FAPhead::operator=(const FAPhead& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void FAPhead::copy(const FAPhead& other)
{
    this->FapType = other.FapType;
    this->R = other.R;
    this->I = other.I;
    this->M = other.M;
    this->counter = other.counter;
    this->seq = other.seq;
    this->Source = other.Source;
    this->Dest = other.Dest;
    this->IDnumber = other.IDnumber;
    this->filterValue = other.filterValue;
    this->filterM = other.filterM;
    this->filterK = other.filterK;
    this->Signature1 = other.Signature1;
    this->Signature2 = other.Signature2;
}

void FAPhead::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->FapType);
    doParsimPacking(b,this->R);
    doParsimPacking(b,this->I);
    doParsimPacking(b,this->M);
    doParsimPacking(b,this->counter);
    doParsimPacking(b,this->seq);
    doParsimPacking(b,this->Source);
    doParsimPacking(b,this->Dest);
    doParsimPacking(b,this->IDnumber);
    doParsimPacking(b,this->filterValue);
    doParsimPacking(b,this->filterM);
    doParsimPacking(b,this->filterK);
    doParsimPacking(b,this->Signature1);
    doParsimPacking(b,this->Signature2);
}

void FAPhead::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->FapType);
    doParsimUnpacking(b,this->R);
    doParsimUnpacking(b,this->I);
    doParsimUnpacking(b,this->M);
    doParsimUnpacking(b,this->counter);
    doParsimUnpacking(b,this->seq);
    doParsimUnpacking(b,this->Source);
    doParsimUnpacking(b,this->Dest);
    doParsimUnpacking(b,this->IDnumber);
    doParsimUnpacking(b,this->filterValue);
    doParsimUnpacking(b,this->filterM);
    doParsimUnpacking(b,this->filterK);
    doParsimUnpacking(b,this->Signature1);
    doParsimUnpacking(b,this->Signature2);
}

inet::FAPmsgType FAPhead::getFapType() const
{
    return this->FapType;
}

void FAPhead::setFapType(inet::FAPmsgType FapType)
{
    handleChange();
    this->FapType = FapType;
}

bool FAPhead::getR() const
{
    return this->R;
}

void FAPhead::setR(bool R)
{
    handleChange();
    this->R = R;
}

bool FAPhead::getI() const
{
    return this->I;
}

void FAPhead::setI(bool I)
{
    handleChange();
    this->I = I;
}

bool FAPhead::getM() const
{
    return this->M;
}

void FAPhead::setM(bool M)
{
    handleChange();
    this->M = M;
}

int FAPhead::getCounter() const
{
    return this->counter;
}

void FAPhead::setCounter(int counter)
{
    handleChange();
    this->counter = counter;
}

int FAPhead::getSeq() const
{
    return this->seq;
}

void FAPhead::setSeq(int seq)
{
    handleChange();
    this->seq = seq;
}

const Ipv4Address& FAPhead::getSource() const
{
    return this->Source;
}

void FAPhead::setSource(const Ipv4Address& Source)
{
    handleChange();
    this->Source = Source;
}

const Ipv4Address& FAPhead::getDest() const
{
    return this->Dest;
}

void FAPhead::setDest(const Ipv4Address& Dest)
{
    handleChange();
    this->Dest = Dest;
}

unsigned int FAPhead::getIDnumber() const
{
    return this->IDnumber;
}

void FAPhead::setIDnumber(unsigned int IDnumber)
{
    handleChange();
    this->IDnumber = IDnumber;
}

const char * FAPhead::getFilterValue() const
{
    return this->filterValue.c_str();
}

void FAPhead::setFilterValue(const char * filterValue)
{
    handleChange();
    this->filterValue = filterValue;
}

unsigned int FAPhead::getFilterM() const
{
    return this->filterM;
}

void FAPhead::setFilterM(unsigned int filterM)
{
    handleChange();
    this->filterM = filterM;
}

unsigned int FAPhead::getFilterK() const
{
    return this->filterK;
}

void FAPhead::setFilterK(unsigned int filterK)
{
    handleChange();
    this->filterK = filterK;
}

unsigned long FAPhead::getSignature1() const
{
    return this->Signature1;
}

void FAPhead::setSignature1(unsigned long Signature1)
{
    handleChange();
    this->Signature1 = Signature1;
}

unsigned long FAPhead::getSignature2() const
{
    return this->Signature2;
}

void FAPhead::setSignature2(unsigned long Signature2)
{
    handleChange();
    this->Signature2 = Signature2;
}

class FAPheadDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
    enum FieldConstants {
        FIELD_FapType,
        FIELD_R,
        FIELD_I,
        FIELD_M,
        FIELD_counter,
        FIELD_seq,
        FIELD_Source,
        FIELD_Dest,
        FIELD_IDnumber,
        FIELD_filterValue,
        FIELD_filterM,
        FIELD_filterK,
        FIELD_Signature1,
        FIELD_Signature2,
    };
  public:
    FAPheadDescriptor();
    virtual ~FAPheadDescriptor();

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

Register_ClassDescriptor(FAPheadDescriptor)

FAPheadDescriptor::FAPheadDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::FAPhead)), "inet::FieldsChunk")
{
    propertynames = nullptr;
}

FAPheadDescriptor::~FAPheadDescriptor()
{
    delete[] propertynames;
}

bool FAPheadDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FAPhead *>(obj)!=nullptr;
}

const char **FAPheadDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FAPheadDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FAPheadDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int FAPheadDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_FapType
        FD_ISEDITABLE,    // FIELD_R
        FD_ISEDITABLE,    // FIELD_I
        FD_ISEDITABLE,    // FIELD_M
        FD_ISEDITABLE,    // FIELD_counter
        FD_ISEDITABLE,    // FIELD_seq
        0,    // FIELD_Source
        0,    // FIELD_Dest
        FD_ISEDITABLE,    // FIELD_IDnumber
        FD_ISEDITABLE,    // FIELD_filterValue
        FD_ISEDITABLE,    // FIELD_filterM
        FD_ISEDITABLE,    // FIELD_filterK
        FD_ISEDITABLE,    // FIELD_Signature1
        FD_ISEDITABLE,    // FIELD_Signature2
    };
    return (field >= 0 && field < 14) ? fieldTypeFlags[field] : 0;
}

const char *FAPheadDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "FapType",
        "R",
        "I",
        "M",
        "counter",
        "seq",
        "Source",
        "Dest",
        "IDnumber",
        "filterValue",
        "filterM",
        "filterK",
        "Signature1",
        "Signature2",
    };
    return (field >= 0 && field < 14) ? fieldNames[field] : nullptr;
}

int FAPheadDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0] == 'F' && strcmp(fieldName, "FapType") == 0) return base+0;
    if (fieldName[0] == 'R' && strcmp(fieldName, "R") == 0) return base+1;
    if (fieldName[0] == 'I' && strcmp(fieldName, "I") == 0) return base+2;
    if (fieldName[0] == 'M' && strcmp(fieldName, "M") == 0) return base+3;
    if (fieldName[0] == 'c' && strcmp(fieldName, "counter") == 0) return base+4;
    if (fieldName[0] == 's' && strcmp(fieldName, "seq") == 0) return base+5;
    if (fieldName[0] == 'S' && strcmp(fieldName, "Source") == 0) return base+6;
    if (fieldName[0] == 'D' && strcmp(fieldName, "Dest") == 0) return base+7;
    if (fieldName[0] == 'I' && strcmp(fieldName, "IDnumber") == 0) return base+8;
    if (fieldName[0] == 'f' && strcmp(fieldName, "filterValue") == 0) return base+9;
    if (fieldName[0] == 'f' && strcmp(fieldName, "filterM") == 0) return base+10;
    if (fieldName[0] == 'f' && strcmp(fieldName, "filterK") == 0) return base+11;
    if (fieldName[0] == 'S' && strcmp(fieldName, "Signature1") == 0) return base+12;
    if (fieldName[0] == 'S' && strcmp(fieldName, "Signature2") == 0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FAPheadDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::FAPmsgType",    // FIELD_FapType
        "bool",    // FIELD_R
        "bool",    // FIELD_I
        "bool",    // FIELD_M
        "int",    // FIELD_counter
        "int",    // FIELD_seq
        "inet::Ipv4Address",    // FIELD_Source
        "inet::Ipv4Address",    // FIELD_Dest
        "unsigned int",    // FIELD_IDnumber
        "string",    // FIELD_filterValue
        "unsigned int",    // FIELD_filterM
        "unsigned int",    // FIELD_filterK
        "unsigned long",    // FIELD_Signature1
        "unsigned long",    // FIELD_Signature2
    };
    return (field >= 0 && field < 14) ? fieldTypeStrings[field] : nullptr;
}

const char **FAPheadDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_FapType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *FAPheadDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case FIELD_FapType:
            if (!strcmp(propertyname, "enum")) return "inet::FAPmsgType";
            return nullptr;
        default: return nullptr;
    }
}

int FAPheadDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FAPhead *pp = (FAPhead *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FAPheadDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FAPhead *pp = (FAPhead *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FAPheadDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FAPhead *pp = (FAPhead *)object; (void)pp;
    switch (field) {
        case FIELD_FapType: return enum2string(pp->getFapType(), "inet::FAPmsgType");
        case FIELD_R: return bool2string(pp->getR());
        case FIELD_I: return bool2string(pp->getI());
        case FIELD_M: return bool2string(pp->getM());
        case FIELD_counter: return long2string(pp->getCounter());
        case FIELD_seq: return long2string(pp->getSeq());
        case FIELD_Source: return pp->getSource().str();
        case FIELD_Dest: return pp->getDest().str();
        case FIELD_IDnumber: return ulong2string(pp->getIDnumber());
        case FIELD_filterValue: return oppstring2string(pp->getFilterValue());
        case FIELD_filterM: return ulong2string(pp->getFilterM());
        case FIELD_filterK: return ulong2string(pp->getFilterK());
        case FIELD_Signature1: return ulong2string(pp->getSignature1());
        case FIELD_Signature2: return ulong2string(pp->getSignature2());
        default: return "";
    }
}

bool FAPheadDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FAPhead *pp = (FAPhead *)object; (void)pp;
    switch (field) {
        case FIELD_FapType: pp->setFapType((inet::FAPmsgType)string2enum(value, "inet::FAPmsgType")); return true;
        case FIELD_R: pp->setR(string2bool(value)); return true;
        case FIELD_I: pp->setI(string2bool(value)); return true;
        case FIELD_M: pp->setM(string2bool(value)); return true;
        case FIELD_counter: pp->setCounter(string2long(value)); return true;
        case FIELD_seq: pp->setSeq(string2long(value)); return true;
        case FIELD_IDnumber: pp->setIDnumber(string2ulong(value)); return true;
        case FIELD_filterValue: pp->setFilterValue((value)); return true;
        case FIELD_filterM: pp->setFilterM(string2ulong(value)); return true;
        case FIELD_filterK: pp->setFilterK(string2ulong(value)); return true;
        case FIELD_Signature1: pp->setSignature1(string2ulong(value)); return true;
        case FIELD_Signature2: pp->setSignature2(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FAPheadDescriptor::getFieldStructName(int field) const
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

void *FAPheadDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FAPhead *pp = (FAPhead *)object; (void)pp;
    switch (field) {
        case FIELD_Source: return toVoidPtr(&pp->getSource()); break;
        case FIELD_Dest: return toVoidPtr(&pp->getDest()); break;
        default: return nullptr;
    }
}

} // namespace inet

