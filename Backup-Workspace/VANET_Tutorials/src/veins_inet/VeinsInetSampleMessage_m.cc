//
// Generated file, do not edit! Created by opp_msgtool 6.0 from veins_inet/VeinsInetSampleMessage.msg.
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
#include <type_traits>
#include "VeinsInetSampleMessage_m.h"

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

Register_Class(VeinsInetSampleMessage)

VeinsInetSampleMessage::VeinsInetSampleMessage() : ::inet::FieldsChunk()
{
}

VeinsInetSampleMessage::VeinsInetSampleMessage(const VeinsInetSampleMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

VeinsInetSampleMessage::~VeinsInetSampleMessage()
{
}

VeinsInetSampleMessage& VeinsInetSampleMessage::operator=(const VeinsInetSampleMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void VeinsInetSampleMessage::copy(const VeinsInetSampleMessage& other)
{
    this->senderId = other.senderId;
    this->posX = other.posX;
    this->posY = other.posY;
    this->requestJunction = other.requestJunction;
}

void VeinsInetSampleMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->posX);
    doParsimPacking(b,this->posY);
    doParsimPacking(b,this->requestJunction);
}

void VeinsInetSampleMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->posX);
    doParsimUnpacking(b,this->posY);
    doParsimUnpacking(b,this->requestJunction);
}

const char * VeinsInetSampleMessage::getSenderId() const
{
    return this->senderId.c_str();
}

void VeinsInetSampleMessage::setSenderId(const char * senderId)
{
    handleChange();
    this->senderId = senderId;
}

double VeinsInetSampleMessage::getPosX() const
{
    return this->posX;
}

void VeinsInetSampleMessage::setPosX(double posX)
{
    handleChange();
    this->posX = posX;
}

double VeinsInetSampleMessage::getPosY() const
{
    return this->posY;
}

void VeinsInetSampleMessage::setPosY(double posY)
{
    handleChange();
    this->posY = posY;
}

bool VeinsInetSampleMessage::getRequestJunction() const
{
    return this->requestJunction;
}

void VeinsInetSampleMessage::setRequestJunction(bool requestJunction)
{
    handleChange();
    this->requestJunction = requestJunction;
}

class VeinsInetSampleMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderId,
        FIELD_posX,
        FIELD_posY,
        FIELD_requestJunction,
    };
  public:
    VeinsInetSampleMessageDescriptor();
    virtual ~VeinsInetSampleMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VeinsInetSampleMessageDescriptor)

VeinsInetSampleMessageDescriptor::VeinsInetSampleMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VeinsInetSampleMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

VeinsInetSampleMessageDescriptor::~VeinsInetSampleMessageDescriptor()
{
    delete[] propertyNames;
}

bool VeinsInetSampleMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VeinsInetSampleMessage *>(obj)!=nullptr;
}

const char **VeinsInetSampleMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VeinsInetSampleMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VeinsInetSampleMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int VeinsInetSampleMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderId
        FD_ISEDITABLE,    // FIELD_posX
        FD_ISEDITABLE,    // FIELD_posY
        FD_ISEDITABLE,    // FIELD_requestJunction
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *VeinsInetSampleMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderId",
        "posX",
        "posY",
        "requestJunction",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int VeinsInetSampleMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "posX") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "posY") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "requestJunction") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *VeinsInetSampleMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_senderId
        "double",    // FIELD_posX
        "double",    // FIELD_posY
        "bool",    // FIELD_requestJunction
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **VeinsInetSampleMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VeinsInetSampleMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VeinsInetSampleMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VeinsInetSampleMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VeinsInetSampleMessage'", field);
    }
}

const char *VeinsInetSampleMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VeinsInetSampleMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return oppstring2string(pp->getSenderId());
        case FIELD_posX: return double2string(pp->getPosX());
        case FIELD_posY: return double2string(pp->getPosY());
        case FIELD_requestJunction: return bool2string(pp->getRequestJunction());
        default: return "";
    }
}

void VeinsInetSampleMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId((value)); break;
        case FIELD_posX: pp->setPosX(string2double(value)); break;
        case FIELD_posY: pp->setPosY(string2double(value)); break;
        case FIELD_requestJunction: pp->setRequestJunction(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VeinsInetSampleMessage'", field);
    }
}

omnetpp::cValue VeinsInetSampleMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return pp->getSenderId();
        case FIELD_posX: return pp->getPosX();
        case FIELD_posY: return pp->getPosY();
        case FIELD_requestJunction: return pp->getRequestJunction();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VeinsInetSampleMessage' as cValue -- field index out of range?", field);
    }
}

void VeinsInetSampleMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId(value.stringValue()); break;
        case FIELD_posX: pp->setPosX(value.doubleValue()); break;
        case FIELD_posY: pp->setPosY(value.doubleValue()); break;
        case FIELD_requestJunction: pp->setRequestJunction(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VeinsInetSampleMessage'", field);
    }
}

const char *VeinsInetSampleMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VeinsInetSampleMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VeinsInetSampleMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VeinsInetSampleMessage *pp = omnetpp::fromAnyPtr<VeinsInetSampleMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VeinsInetSampleMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

