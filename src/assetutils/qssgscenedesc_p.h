// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QSSGSCENEDESCRIPTION_P_H
#define QSSGSCENEDESCRIPTION_P_H

#include <QtQuick3DAssetUtils/private/qtquick3dassetutilsglobal_p.h>
#include <QtQuick3DRuntimeRender/private/qssgrendergraphobject_p.h>
#include <QtQuick3DRuntimeRender/private/qssgperframeallocator_p.h>
#include <QtQuick3DUtils/private/qssgmesh_p.h>

#include <QtCore/qlist.h>
#include <QtCore/qhash.h>
#include <QtCore/qvariant.h>
#include <QtCore/qflags.h>
#include <QtQml/qqmllist.h>

// QtQuick3D
#include <QtQuick3D/private/qquick3dobject_p.h>
// Materials
#include <QtQuick3D/private/qquick3dcustommaterial_p.h>
#include <QtQuick3D/private/qquick3ddefaultmaterial_p.h>
#include <QtQuick3D/private/qquick3dprincipledmaterial_p.h>
#include <QtQuick3D/private/qquick3dspecularglossymaterial_p.h>
#include <QtQuick3D/private/qquick3dmodel_p.h>
// cameras
#include <QtQuick3D/private/qquick3dorthographiccamera_p.h>
#include <QtQuick3D/private/qquick3dperspectivecamera_p.h>
#include <QtQuick3D/private/qquick3dcustomcamera_p.h>
// Lights
#include <QtQuick3D/private/qquick3ddirectionallight_p.h>
#include <QtQuick3D/private/qquick3dpointlight_p.h>
#include <QtQuick3D/private/qquick3dspotlight_p.h>
// Texture
#include <QtQuick3D/private/qquick3dtexture_p.h>
#include <QtQuick3D/private/qquick3dcubemaptexture_p.h>
#include <QtQuick3D/private/qquick3dtexturedata_p.h>
//
#include <QtQuick3D/private/qquick3dskeleton_p.h>
#include <QtQuick3D/private/qquick3djoint_p.h>

#include <qmetatype.h>
#include <QtQuick3DUtils/private/qssginvasivelinkedlist_p.h>


QT_BEGIN_NAMESPACE

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

namespace QSSGSceneDesc
{

struct Node;
struct Animation;

template<typename T>
using rm_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

struct Q_QUICK3DASSETUTILS_EXPORT Scene
{
    using ResourceNodes = QVarLengthArray<Node *>;
    using MeshStorage = QVector<QSSGMesh::Mesh>;
    using Allocator = QSSGPerFrameAllocator;
    using Animations = QVector<Animation *>;

    // Root node, usually an empty 'transform' node.
    Node *root = nullptr;
    QString id; // Don't make any assumption about the content of this id...
    ResourceNodes resources;
    MeshStorage meshStorage;
    Animations animations;
    QString sourceDir;
    mutable quint16 nodeId = 0;

    void reset();
};

struct Q_QUICK3DASSETUTILS_EXPORT PropertyCall
{
    virtual bool set(QQuick3DObject &, const char *, const void *) = 0;
    virtual bool get(const QQuick3DObject &, const void *[]) const = 0;
};

struct Value
{
    QMetaType mt;
    void *dptr;
};

Q_QUICK3DASSETUTILS_EXPORT void destructValue(QSSGSceneDesc::Value &value);

struct Flag
{
    QMetaEnum me;
    quintptr value;
};

struct BufferView {
    using type = QByteArray;
    QByteArray view;
};
struct UrlView : BufferView { using type = QUrl; };
struct StringView : BufferView { using type = QString; };

struct Property
{
    ~Property();
    enum class Type { Static, Dynamic };
    Value value;
    const char *name = nullptr;
    QSSGSceneDesc::PropertyCall *call = nullptr;
    Type type = Type::Static;
};

inline Property::~Property()
{
    destructValue(value);
}

Q_QUICK3DASSETUTILS_EXPORT void destructNode(QSSGSceneDesc::Node &node);

struct NodeList
{
    ~NodeList() { if (head) free(head); }
    Node **head = nullptr;
    qsizetype count = -1;
};

struct Node
{
    // Node type
    enum class Type : quint8
    {
        Transform,
        Camera,
        Model,
        Texture,
        Material,
        Light,
        Mesh,
        Skin,
        Skeleton,
        Joint,
        MorphTarget
    };

    using type = QQuick3DNode;
    // Runtime type type mapping between this type and the QtQuick3D type
    using RuntimeType = QSSGRenderGraphObject::Type;

    explicit Node(QByteArray name, Node::Type type, Node::RuntimeType rt)
        : name(name)
        , runtimeType(rt)
        , nodeType(type) {}
    explicit Node(Node::Type type, Node::RuntimeType rt)
        : Node(nullptr, type, rt) {}

    ~Node() { destructNode(*this); }

    QByteArray name;
    Scene *scene = nullptr;
    QObject *obj = nullptr;
    using ChildList = QList<Node *>;
    using PropertyList = QList<Property *>;
    ChildList children;
    PropertyList properties;
    quint16 id = 0;
    RuntimeType runtimeType;
    Type nodeType;
};

template<typename T>
static constexpr bool is_node_v = std::is_base_of_v<Node, T>;

// Set up type mapping from a QQuick3D type to a SceneDesc type
template <typename T> struct TypeMap {};
#define QSSG_DECLARE_NODE(NODE) \
static_assert(is_node_v<NODE>, #NODE " - does not inherit from Node!"); \
template <> struct TypeMap<NODE::type> { using type = QSSGSceneDesc::NODE; };

template<typename T>
using as_scene_type_t = typename T::type;
template<typename T>
using as_node_type_t = typename TypeMap<T>::type;

QSSG_DECLARE_NODE(Node)

struct Texture : Node
{
    using type = QQuick3DTexture;
    Texture(Node::RuntimeType rt, const QByteArray &name = {})
        : Node(name, Node::Type::Texture, rt)
    {
    }
};
QSSG_DECLARE_NODE(Texture)

struct TextureData : Node
{
    using type = QQuick3DTextureData;
    enum class Flags : quint8
    {
        Compressed = 0x1
    };

    using Format = QQuick3DTextureData::Format;
    explicit TextureData(const QByteArray &textureData, QSize size, Format format, quint8 flags = 0, QByteArray name = {})
        : Node(name, Node::Type::Texture, RuntimeType::TextureData)
        , data(textureData)
        , sz(size)
        , fmt(format)
        , flgs(flags)
    {}
    QByteArray data;
    QSize sz;
    Format fmt;
    quint8 flgs;
};
QSSG_DECLARE_NODE(TextureData)

struct Material : Node
{
    using type = QQuick3DMaterial;
    explicit Material(Node::RuntimeType rt) : Node(Node::Type::Material, rt) {}
};
QSSG_DECLARE_NODE(Material)

// The mesh is a special node, as it's not really a node type but
// a handle to a mesh that will be turned into a source URL...
struct Mesh : Node
{
    explicit Mesh(QByteArray name, qsizetype index)
        : Node(name, Node::Type::Mesh, RuntimeType::Node)
        , idx(index)
    {}
    qsizetype idx; // idx to the mesh data in the mesh data storage (see Scene).
};

struct Model : Node
{
    using type = QQuick3DModel;
    Model() : Node(Node::Type::Model, Node::RuntimeType::Model) {}
};
QSSG_DECLARE_NODE(Model)

struct Camera : Node
{
    using type = QQuick3DCamera;
    explicit Camera(RuntimeType rt) : Node(Node::Type::Camera, rt) {}
};
QSSG_DECLARE_NODE(Camera)

struct Light : Node
{
    using type = QQuick3DAbstractLight;
    explicit Light(RuntimeType rt) : Node(Node::Type::Light, rt) {}
};
QSSG_DECLARE_NODE(Light)

struct Skin : Node
{
    using type = QQuick3DSkin;
    Skin() : Node(Node::Type::Skin, Node::RuntimeType::Skin) {}
};
QSSG_DECLARE_NODE(Skin)

struct Skeleton : Node
{
    using type = QQuick3DSkeleton;
    Skeleton() : Node(Node::Type::Skeleton, Node::RuntimeType::Skeleton) {}
    // Skeleton is a virtual node, which is added for the start of the joint heirarchy.
    // parent - joint 1     ->      parent - skeleton - joint 1
    //        - joint 2                               - joint 2
    //        - model 1                    - model 1
    //        - camera 1                   - camera 1
    size_t maxIndex = 0;
};
QSSG_DECLARE_NODE(Skeleton)

struct Joint : Node
{
    using type = QQuick3DJoint;
    Joint() : Node(Node::Type::Joint, Node::RuntimeType::Joint) {}
};
QSSG_DECLARE_NODE(Joint)

struct MorphTarget : Node
{
    using type = QQuick3DMorphTarget;
    MorphTarget() : Node(Node::Type::MorphTarget, Node::RuntimeType::MorphTarget) {}
};
QSSG_DECLARE_NODE(MorphTarget)

struct ListView
{
    ~ListView() { if (head.dptr) free(head.dptr); }
    Value head;
    qsizetype count = -1;
};

Q_QUICK3DASSETUTILS_EXPORT QMetaType listViewMetaType();
Q_QUICK3DASSETUTILS_EXPORT QMetaType flagMetaType();

struct Animation
{
    struct KeyPosition
    {
        enum class KeyType : quint16
        {
            Frame = 0x100,
            Time = 0x200
        };

        enum class ValueType : quint8
        {
            Number,
            Vec2,
            Vec3,
            Vec4,
            Quaternion
        };

        ValueType getValueType() const { return ValueType(0xf & flag); }
        KeyType getKeyType() const { return KeyType(0xf00 & flag); }
        QVariant getValue() const {
            switch (getValueType()) {
            case ValueType::Number:
                return value.x();
            case ValueType::Vec2:
                return value.toVector2D();
            case ValueType::Vec3:
                return value.toVector3D();
            case ValueType::Vec4:
                return value;
            case ValueType::Quaternion:
                return QQuaternion(value);
            }
            return value;
        }
        QMetaType::Type getValueQMetaType() const {
            switch (getValueType()) {
            case ValueType::Number:
                return QMetaType::Float;
            case ValueType::Vec2:
                return QMetaType::QVector2D;
            case ValueType::Vec3:
                return QMetaType::QVector3D;
            case ValueType::Vec4:
                return QMetaType::QVector4D;
            case ValueType::Quaternion:
                return QMetaType::QQuaternion;
            }
            return QMetaType::QVector4D;
        }
        QVector4D value;
        float time = 0.0f;
        quint16 flag = 0;
    };
    using Keys = QList<Animation::KeyPosition *>;

    struct Channel
    {
        enum class TargetType : quint8
        {
            Property
        };

        // This is a bit simplistic, but is all we support so let's keep simple.
        enum class TargetProperty : quint8
        {
            Unknown,
            Position,
            Rotation,
            Scale,
            Weight // for MorphMesh
        };

        Node *target = nullptr;
        Keys keys;
        TargetType targetType = TargetType::Property;
        TargetProperty targetProperty = TargetProperty::Unknown;
    };
    using Channels = QList<Animation::Channel *>;

    Channels channels;
    // It stores the length of this Animation, every keys in every channels in
    // an animation will have the same KeyType and it will be a type of
    // the length
    float length = 0.0f;
};

// Add a child node to parent node.
Q_QUICK3DASSETUTILS_EXPORT void addNode(Node &parent, Node &node);
// Add node to the scene, if a node is already set the new node will
// become a child of the root node.
Q_QUICK3DASSETUTILS_EXPORT void addNode(Scene &scene, Node &node);

template<typename> struct ListParam { enum { value = 0 }; };
template<typename T> struct ListParam<QList<T>>
{
    using type = T;
    enum { value = 1 };
};

template <typename T>
using listParam_t = typename ListParam<rm_cvref_t<T>>::type;

template <typename T>
struct FuncType
{
    enum { value = 0 };
};

template <typename R, typename... A>
struct FuncType<R (*)(A...)>
{
    enum { value = sizeof...(A) == 3 };
    using Ret = R;
    using Arg0 = std::tuple_element_t<0, std::tuple<A...>>;
    using Arg1 = std::tuple_element_t<1, std::tuple<A...>>;
    using Arg2 = std::tuple_element_t<2, std::tuple<A...>>;
    using Arg2Base = rm_cvref_t<Arg2>;
};

template <typename R, typename C, typename... A>
struct FuncType<R (C::*)(A...)>
{
    enum { value = sizeof... (A) == 1 };
    using Ret = R;
    using Class = C;
    // For now we only care about single argument functions
    using Arg0 = std::tuple_element_t<0, std::tuple<A...>>;
    using Arg0Base = rm_cvref_t<Arg0>;
};

template <typename T, typename C>
struct FuncType<QQmlListProperty<T> (C::*)()>
{
    enum { value = 2 };
    using Ret = QQmlListProperty<T>;
    using Class = C;
    using Arg0 = void;
    using Arg0Base = Arg0;
};

template <typename T>
constexpr bool can_be_stored_in_pointer()
{
    return sizeof(T) <= sizeof(void *) && std::is_trivially_copyable_v<T>;
}

bool can_be_stored_in_pointer(const QMetaType &mt);

template <typename T>
constexpr T type_pun_cast_value(const void **ptr)
{
    void *p = ptr;
    return *static_cast<T *>(p);
}

template <typename Ret, typename Arg>
struct PropertyProxySetter : PropertyCall
{
    using Setter = Ret (*)(QQuick3DObject &, const char *, Arg);
    constexpr explicit PropertyProxySetter(Setter fn) : call(fn) {}
    Setter call = nullptr;
    bool get(const QQuick3DObject &, const void *[]) const override { return false; }
    bool set(QQuick3DObject &that, const char *name, const void *value) override
    {
        using ArgT = typename FuncType<Setter>::Arg2Base;
        if constexpr (std::is_pointer_v<typename FuncType<Setter>::Arg2>)
            call(that, name, reinterpret_cast<typename FuncType<Setter>::Arg2>(const_cast<void *>(value)));
        else if constexpr (can_be_stored_in_pointer<ArgT>())
            call(that, name, type_pun_cast_value<ArgT>(&value));
        else
            call(that, name, *reinterpret_cast<ArgT *>(const_cast<void *>(value)));
        return true;
    }
};

template <typename Ret, typename Class, typename Arg>
struct PropertySetter : PropertyCall
{
    using Setter = Ret (Class::*)(Arg);
    constexpr explicit PropertySetter(Setter fn) : call(fn) {}
    Setter call = nullptr;
    bool get(const QQuick3DObject &, const void *[]) const override { return false; }
    bool set(QQuick3DObject &that, const char *, const void *value) override
    {
        using ArgT = typename FuncType<Setter>::Arg0Base;
        if constexpr (std::is_pointer_v<typename FuncType<Setter>::Arg0>) {
            (qobject_cast<Class *>(&that)->*call)(reinterpret_cast<typename FuncType<Setter>::Arg0>(const_cast<void *>(value)));
        } else if constexpr (can_be_stored_in_pointer<ArgT>()) {
            (qobject_cast<Class *>(&that)->*call)(type_pun_cast_value<ArgT>(&value));
        } else {
            (qobject_cast<Class *>(&that)->*call)(*reinterpret_cast<typename FuncType<Setter>::Arg0Base *>(const_cast<void *>(value)));
        }
        return true;
    }
};

template <typename Ret, typename Class, typename Arg>
struct PropertyListSetter : PropertyCall
{
    using Setter = Ret (Class::*)(Arg);
    using ListT = typename FuncType<Setter>::Arg0Base;
    using It = listParam_t<ListT>;
    constexpr explicit PropertyListSetter(Setter fn) : call(fn) {}
    Setter call = nullptr;
    bool get(const QQuick3DObject &, const void *[]) const override { return false; }
    bool set(QQuick3DObject &that, const char *, const void *value) override
    {
        if (const auto listView = reinterpret_cast<const ListView *>(value)) {
            if (listView->count > 0) {
                const auto begin = reinterpret_cast<It *>(listView->head.dptr);
                const auto end = reinterpret_cast<It *>(listView->head.dptr) + listView->count;
                (qobject_cast<Class *>(&that)->*call)(ListT{begin, end});
            } else {
                (qobject_cast<Class *>(&that)->*call)(ListT{});
            }
            return true;
        }

        return false;
    }
};

template <typename Class, typename T, template <typename> typename List>
struct PropertyList : PropertyCall
{
    using ListType = List<T>;
    using ListFunc = ListType (Class::*)();
    constexpr explicit PropertyList(ListFunc fn) : listfn(fn) {}
    ListFunc listfn = nullptr;

    static_assert(std::is_same_v<ListType, QQmlListProperty<T>>, "Expected QQmlListProperty!");

    bool get(const QQuick3DObject &, const void *[]) const override { return false; }
    bool set(QQuick3DObject &that, const char *, const void *value) override
    {
        if (value) {
            ListType list = (qobject_cast<Class *>(&that)->*listfn)();
            const auto &nodeList = *reinterpret_cast<const QSSGSceneDesc::NodeList *>(value);
            auto head = reinterpret_cast<as_node_type_t<T> **>(nodeList.head);
            for (int i = 0, end = nodeList.count; i != end; ++i)
                list.append(&list, qobject_cast<T *>((*(head + i))->obj));
            return true;
        }

        return false;
    }
};

template <typename NodeT>
using if_node = typename std::enable_if_t<is_node_v<NodeT>, bool>;
template <typename Setter, typename Value>
using if_compatible_t = typename std::enable_if_t<std::is_same_v<typename FuncType<Setter>::Arg0Base, rm_cvref_t<Value>>, bool>;
template <typename Setter, typename T>
using if_compatible_node_list_t = typename std::enable_if_t<std::is_same_v<typename FuncType<Setter>::Ret, QQmlListProperty<as_scene_type_t<T>>>, bool>;
template <typename Setter, typename Value>
using if_compatible_proxy_t = typename std::enable_if_t<std::is_same_v<typename FuncType<Setter>::Arg2Base, rm_cvref_t<Value>>, bool>;

// Sets a property on a node, the property is a name map to struct containing a pointer to the value and a function
// to set the value on an runtime object (QtQuick3DObject). The type is verified at compile-time, so we can assume
// the value is of the right type when setting it at run-time.
template<typename Setter, typename T, if_compatible_t<Setter, T> = false>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, T &&value)
{
    Q_ASSERT(node.scene);
    using Tt = rm_cvref_t<T>;
    static_assert(std::is_trivially_destructible_v<Tt>, "Value needs to be trivially destructible!");
    auto prop = new Property;
    prop->name = name;
    prop->call = new PropertySetter(setter);
    prop->value.mt = QMetaType::fromType<Tt>();
    if constexpr (can_be_stored_in_pointer<Tt>()) {
        Tt *dest = reinterpret_cast<Tt *>(&prop->value.dptr);
        *dest = value;
    } else {
        prop->value.dptr = new Tt(std::forward<T>(value));
    }
    node.properties.push_back(prop);
}

template<typename Setter, typename T, if_compatible_t<Setter, QFlags<T>> = false>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, QFlags<T> value)
{
    Q_ASSERT(node.scene);
    auto prop = new Property;
    prop->name = name;
    prop->call = new PropertySetter(setter);
    prop->value.mt = flagMetaType();
    prop->value.dptr = new Flag{ QMetaEnum::fromType<rm_cvref_t<T>>(), quintptr(value) };
    node.properties.push_back(prop);
}

template<typename Setter, typename T, if_compatible_t<Setter, QList<T>> = false>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, QList<T> value)
{
    Q_ASSERT(node.scene);
    static_assert(!std::is_pointer_v<T>, "Type cannot be a pointer!");
    static_assert(std::is_trivially_destructible_v<T> && std::is_trivially_copy_constructible_v<T>,
            "List parameter type needs to be trivially constructable and trivially destructible!");

    const auto count = value.size();
    void *data = nullptr;
    if (count) {
        const auto asize = count * sizeof(T);
        data = malloc(asize); // is freed in ~ListView
        memcpy(data, value.constData(), asize);
    }
    auto prop = new Property;
    prop->name = name;
    prop->call = new PropertyListSetter(setter);
    prop->value.mt = listViewMetaType();
    prop->value.dptr = new ListView{ { QMetaType::fromType<rm_cvref_t<T>>(), data }, count };
    node.properties.push_back(prop);
}

// Calling this will omit any type checking, so make sure the type is handled correctly
// when it gets used later!
template<typename Setter>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, QSSGSceneDesc::Value &&value)
{
    Q_ASSERT(node.scene);
    Property *prop = new Property;
    prop->name = name;
    prop->call = new PropertySetter(setter);
    prop->value = value;
    node.properties.push_back(prop);
}

// Only used from the material editor so far
template<typename Setter, typename Value, if_compatible_proxy_t<Setter, Value> = true>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, Value &&value, QSSGSceneDesc::Property::Type type = QSSGSceneDesc::Property::Type::Static)
{
    Q_ASSERT(node.scene);
    static_assert(std::is_trivially_destructible_v<rm_cvref_t<Value>>, "Value needs to be trivially destructible!");
    Property *prop = new Property;
    prop->name = name;
    prop->call = new PropertyProxySetter(setter);
    using ValueT = rm_cvref_t<Value>;
    prop->value.mt = QMetaType::fromType<ValueT>();
    if constexpr (std::is_pointer_v<ValueT>) {
        prop->value.dptr = value;
    } else if constexpr (can_be_stored_in_pointer<ValueT>()) {
        ValueT *dest = reinterpret_cast<ValueT *>(&prop->value.dptr);
        *dest = value;
    } else {
        prop->value.dptr = new ValueT(std::forward<Value>(value));
    }
    prop->type = type;
    node.properties.push_back(prop);
}

template<typename Setter, typename ViewValue, if_compatible_t<Setter, typename ViewValue::type> = false>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, ViewValue view)
{
    Q_ASSERT(node.scene);
    static_assert(std::is_same_v<typename ViewValue::type, typename FuncType<Setter>::Arg0Base>, "Type cannot be mapped to slot argument");
    Property *prop = new Property;
    prop->name = name;
    prop->call = new PropertySetter(setter);
    using ViewValueT = rm_cvref_t<ViewValue>;
    prop->value.mt = QMetaType::fromType<ViewValueT>();
    prop->value.dptr = new ViewValueT(std::move(view));
    node.properties.push_back(prop);
}

template<typename Setter, typename Value, if_compatible_t<Setter, as_scene_type_t<Value> *> = true>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, Value *value)
{
    Q_ASSERT(node.scene);
    Property *prop = new Property;
    prop->name = name;
    prop->call = new PropertySetter(setter);
    prop->value.mt = QMetaType::fromType<Node *>(); // Always 'Node', the Node class itself contains more fine grain type information.
    prop->value.dptr = value;
    node.properties.push_back(prop);
}

// Overloaded function for setting a type to a property that's a QQmlListProperty.
template<typename Setter, typename NodeT, qsizetype Prealloc, if_compatible_node_list_t<Setter, NodeT> = true>
static void setProperty(QSSGSceneDesc::Node &node, const char *name, Setter setter, const QVarLengthArray<NodeT *, Prealloc> &list)
{
    Q_ASSERT(node.scene);
    if (!list.isEmpty()) {
        NodeList *l = new NodeList;
        {
            const auto size = sizeof(Node *) * list.count();
            l->head = reinterpret_cast<Node **>(malloc(size)); // is freed in ~NodeList()
            memcpy(l->head, list.data(), size);
            l->count = list.size();
        }

        Property *prop = new Property;
        prop->name = name;
        prop->call = new PropertyList(setter);
        prop->value.mt = QMetaType::fromType<QSSGSceneDesc::NodeList *>();
        prop->value.dptr = l;
        node.properties.push_back(prop);
    }
}

} // QSSGSceneDesc

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QSSGSceneDesc::Node)
Q_DECLARE_METATYPE(QSSGSceneDesc::Texture)
Q_DECLARE_METATYPE(QSSGSceneDesc::Material)
Q_DECLARE_METATYPE(QSSGSceneDesc::Mesh)
Q_DECLARE_METATYPE(QSSGSceneDesc::Model)
Q_DECLARE_METATYPE(QSSGSceneDesc::Camera)
Q_DECLARE_METATYPE(QSSGSceneDesc::Light)
Q_DECLARE_METATYPE(QSSGSceneDesc::Skin)
Q_DECLARE_METATYPE(QSSGSceneDesc::Skeleton)
Q_DECLARE_METATYPE(QSSGSceneDesc::Joint)
Q_DECLARE_METATYPE(QSSGSceneDesc::MorphTarget)
Q_DECLARE_METATYPE(QSSGSceneDesc::NodeList)
Q_DECLARE_METATYPE(QSSGSceneDesc::Animation)

Q_DECLARE_METATYPE(QSSGSceneDesc::BufferView)
Q_DECLARE_METATYPE(QSSGSceneDesc::UrlView)
Q_DECLARE_METATYPE(QSSGSceneDesc::StringView)
Q_DECLARE_METATYPE(QSSGSceneDesc::ListView)

Q_DECLARE_METATYPE(QSSGSceneDesc::Flag)

#endif // QSSGSCENEDESCRIPTION_P_H
