
/* Support for dynamic loading of extension modules */

#include "Python.h"

/* ./configure sets HAVE_DYNAMIC_LOADING if dynamic loading of modules is
   supported on this platform. configure will then compile and link in one
   of the dynload_*.c files, as appropriate. We will call a function in
   those modules to get a function pointer to the module's init function.
*/
#ifdef HAVE_DYNAMIC_LOADING

#include "importdl.h"

extern dl_funcptr _PyImport_GetDynLoadFunc(const char *name,
					   const char *shortname,
					   const char *pathname, FILE *fp);



PyObject *
_PyImport_LoadDynamicModule(char *name, char *pathname, FILE *fp)
{
	PyObject *m;
	char *lastdot, *shortname, *packagecontext, *oldcontext;
	dl_funcptr p;

    // 1. 检查module备份
	if ((m = _PyImport_FindExtension(name, pathname)) != NULL) {
		Py_INCREF(m);
		return m;
	}
	lastdot = strrchr(name, '.');
	if (lastdot == NULL) {
		packagecontext = NULL;
		shortname = name;
	}
	else {
		packagecontext = name;
		shortname = lastdot+1;
	}

    // 2. 获取动态模块初始化函数地址
	p = _PyImport_GetDynLoadFunc(name, shortname, pathname, fp);
	if (PyErr_Occurred())
		return NULL;
	if (p == NULL) {
		PyErr_Format(PyExc_ImportError,
		   "dynamic module does not define init function (init%.200s)",
			     shortname);
		return NULL;
	}
        oldcontext = _Py_PackageContext;
	_Py_PackageContext = packagecontext;
    // 3. 调用初始化函数
	(*p)();
	_Py_PackageContext = oldcontext;
	if (PyErr_Occurred())
		return NULL;

    // 4. 检查module是否被加入sys.modules
	m = PyDict_GetItemString(PyImport_GetModuleDict(), name);
	if (m == NULL) {
		PyErr_SetString(PyExc_SystemError,
				"dynamic module not initialized properly");
		return NULL;
	}
	/* Remember the filename as the __file__ attribute */
    // 5. 设置module __file__属性
	if (PyModule_AddStringConstant(m, "__file__", pathname) < 0)
		PyErr_Clear(); /* Not important enough to report */

    // 6. 备份module
	if (_PyImport_FixupExtension(name, pathname) == NULL)
		return NULL;
	if (Py_VerboseFlag)
		PySys_WriteStderr(
			"import %s # dynamically loaded from %s\n",
			name, pathname);
	Py_INCREF(m);
	return m;
}

#endif /* HAVE_DYNAMIC_LOADING */
