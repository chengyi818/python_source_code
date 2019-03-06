/* Descriptors */
#ifndef Py_DESCROBJECT_H
#define Py_DESCROBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

typedef PyObject *(*getter)(PyObject *, void *);
typedef int (*setter)(PyObject *, PyObject *, void *);

typedef struct PyGetSetDef {
	char *name;
	getter get;
	setter set;
	char *doc;
	void *closure;
} PyGetSetDef;

typedef PyObject *(*wrapperfunc)(PyObject *self, PyObject *args,
				 void *wrapped);

typedef PyObject *(*wrapperfunc_kwds)(PyObject *self, PyObject *args,
				      void *wrapped, PyObject *kwds);

struct wrapperbase {
	char *name;                      // "__add__"
	int offset;                      // 在 PyHeapTypeObject 中的相对偏移
	void *function;                  // 自定义函数重载,替换使用
	wrapperfunc wrapper;             // 外层壳函数
	char *doc;
	int flags;
	PyObject *name_strobj;
};

/* Flags for above struct */
#define PyWrapperFlag_KEYWORDS 1 /* wrapper function takes keyword args */

/* Various kinds of descriptor objects */

#define PyDescr_COMMON \
	PyObject_HEAD \
	PyTypeObject *d_type; \         // descriptor关联的类
	PyObject *d_name                // descriptor关联的类名

typedef struct {
	PyDescr_COMMON;
} PyDescrObject;

typedef struct {
	PyDescr_COMMON;
	PyMethodDef *d_method;
} PyMethodDescrObject;

typedef struct {
	PyDescr_COMMON;
	struct PyMemberDef *d_member;
} PyMemberDescrObject;

typedef struct {
	PyDescr_COMMON;
	PyGetSetDef *d_getset;
} PyGetSetDescrObject;

typedef struct {
	PyDescr_COMMON;
	struct wrapperbase *d_base;
	void *d_wrapped; /* This can be any function pointer */ // 实际调用函数
} PyWrapperDescrObject;

    // typedef struct {
    //     PyObject_HEAD ;
    //     PyTypeObject *d_type;          // descriptor关联的类
    //     PyObject *d_name               // descriptor关联的类名
    //     struct wrapperbase *d_base;
    //     void *d_wrapped;               // 实际调用函数
    // } PyWrapperDescrObject;

PyAPI_DATA(PyTypeObject) PyWrapperDescr_Type;

PyAPI_FUNC(PyObject *) PyDescr_NewMethod(PyTypeObject *, PyMethodDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewClassMethod(PyTypeObject *, PyMethodDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewMember(PyTypeObject *,
					       struct PyMemberDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewGetSet(PyTypeObject *,
					       struct PyGetSetDef *);
PyAPI_FUNC(PyObject *) PyDescr_NewWrapper(PyTypeObject *,
						struct wrapperbase *, void *);
#define PyDescr_IsData(d) ((d)->ob_type->tp_descr_set != NULL)

PyAPI_FUNC(PyObject *) PyDictProxy_New(PyObject *);
PyAPI_FUNC(PyObject *) PyWrapper_New(PyObject *, PyObject *);


PyAPI_DATA(PyTypeObject) PyProperty_Type;
#ifdef __cplusplus
}
#endif
#endif /* !Py_DESCROBJECT_H */
