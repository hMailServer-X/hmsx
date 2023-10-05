#define SS_DANGEROUS_FORMAT
#define SS_ANSI

#if defined(_MSC_VER) && (_MSC_VER > 1100)
	#pragma once
	#pragma component(browser, off, references, "CStdString")
#endif


#ifndef STDSTRING_H
#define STDSTRING_H

#define SS_IS_INTRESOURCE(_r) (false)

#if !defined (SS_ANSI) && defined(_MSC_VER)
	#undef SS_IS_INTRESOURCE
	#if defined(_WIN64)
		#define SS_IS_INTRESOURCE(_r) (((unsigned long long)(_r) >> 16) == 0)
	#else
		#define SS_IS_INTRESOURCE(_r) (((unsigned long)(_r) >> 16) == 0)
	#endif
#endif


#ifdef SS_ALLOW_UNSIGNED_CHARS
	#define SS_UNSIGNED
#endif

#define SS_SAFE_FORMAT 

#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(_WIN32)
    #define SS_WIN32
#endif

#ifndef SS_WIN32
    #if !defined(SS_NO_ANSI)
        #define SS_ANSI
    #endif
#endif

#if defined(_MSC_VER) && !defined(SS_ANSI)
	#define SS_ALLOCA
#endif

#ifdef _MBCS
	#define SS_MBCS
#endif

#ifdef _MSC_VER
	#if defined (_UNICODE) && !defined (UNICODE)
		#error UNICODE defined  but not UNICODE
	//	#define UNICODE  // no longer silently fix this
	#endif
	#if defined (UNICODE) && !defined (_UNICODE)
		#error Warning, UNICODE defined  but not _UNICODE
	//	#define _UNICODE  // no longer silently fix this
	#endif
#endif

template<class Type>
inline const Type& SSMIN(const Type& arg1, const Type& arg2)
{
	return arg2 < arg1 ? arg2 : arg1;
}
template<class Type>
inline const Type& SSMAX(const Type& arg1, const Type& arg2)
{
	return arg2 > arg1 ? arg2 : arg1;
}

#if !defined(W32BASE_H)

	#ifdef SS_ANSI

		#ifdef SS_WIN32

			#include <TCHAR.H>
			#include <WTYPES.H>
			#ifndef STRICT
				#define STRICT
			#endif

		#else

			typedef const char*		PCSTR;
			typedef char*			PSTR;
			typedef const wchar_t*	PCWSTR;
			typedef wchar_t*		PWSTR;
			#ifdef UNICODE
				typedef wchar_t		TCHAR;
			#else
				typedef char		TCHAR;
			#endif
			typedef wchar_t			OLECHAR;

		#endif	// #ifndef _WIN32

		#ifndef ASSERT
			#include <assert.h>
			#define ASSERT(f) assert((f))
		#endif
		#ifndef VERIFY
			#ifdef _DEBUG
				#define VERIFY(x) ASSERT((x))
			#else
				#define VERIFY(x) x
			#endif
		#endif

	#else // ...else SS_ANSI is NOT defined

		#include <TCHAR.H>
		#include <WTYPES.H>
		#ifndef STRICT
			#define STRICT
		#endif

		// Make sure ASSERT and verify are defined

		#ifndef ASSERT
			#include <crtdbg.h>
			#define ASSERT(f) _ASSERTE((f))
		#endif
		#ifndef VERIFY
			#ifdef _DEBUG
				#define VERIFY(x) ASSERT((x))
			#else
				#define VERIFY(x) x
			#endif
		#endif

	#endif // #ifdef SS_ANSI

	#ifndef UNUSED
		#define UNUSED(x) x
	#endif

#endif // #ifndef W32BASE_H

#include <string>			// basic_string
#include <algorithm>		// for_each, etc.
#include <functional>		// for StdStringLessNoCase, et al
#include <locale>			// for various facets

#if defined (_MSC_VER) && (_MSC_VER >= 1100)
	#include <comdef.h>
	#define SS_INC_COMDEF		// signal that we #included MS comdef.h file
	#define STDSTRING_INC_COMDEF
	#define SS_NOTHROW __declspec(nothrow)
#else
	#define SS_NOTHROW
#endif

#ifndef TRACE
	#define TRACE_DEFINED_HERE
	#define TRACE
#endif

#if !defined(PCTSTR) && !defined(PCTSTR_DEFINED)
	typedef const TCHAR*			PCTSTR;
	#define PCTSTR_DEFINED
#endif

#if !defined(PCOLESTR) && !defined(PCOLESTR_DEFINED)
	typedef const OLECHAR*			PCOLESTR;
	#define PCOLESTR_DEFINED
#endif

#if !defined(POLESTR) && !defined(POLESTR_DEFINED)
	typedef OLECHAR*				POLESTR;
	#define POLESTR_DEFINED
#endif

#if !defined(PCUSTR) && !defined(PCUSTR_DEFINED)
	typedef const unsigned char*	PCUSTR;
	typedef unsigned char*			PUSTR;
	#define PCUSTR_DEFINED
#endif

#if defined(__sgi)
    typedef unsigned long           DWORD;
    typedef void *                  LPCVOID;
#endif

#ifndef schMSG
	#define schSTR(x)	   #x
	#define schSTR2(x)	schSTR(x)
	#define schMSG(desc) message(__FILE__ "(" schSTR2(__LINE__) "):" #desc)
#endif

#ifndef SS_USE_FACET

	#if defined(__SGI_STL_PORT) && (__SGI_STL_PORT >= 0x400 )

		#if defined(__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS) && defined(_MSC_VER)
			#ifdef SS_ANSI
				#pragma schMSG(__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS defined!!)
			#endif
		#endif
		#define SS_USE_FACET(loc, fac) std::use_facet<fac >(loc)

	#elif defined(_MSC_VER )

		//#define SS_USE_FACET(loc, fac) std::_USE(loc, fac)
		#define SS_USE_FACET(loc, fac) std::use_facet<fac >(loc)

	// ...and
	#elif defined(_RWSTD_NO_TEMPLATE_ON_RETURN_TYPE)

        #define SS_USE_FACET(loc, fac) std::use_facet(loc, (fac*)0)

	#else

		#define SS_USE_FACET(loc, fac) std::use_facet<fac >(loc)

	#endif

#endif


#include <wchar.h>      // Added to Std Library with Amendment #1.
#include <stdio.h>
#include <stdarg.h>
#include <wctype.h>
#include <ctype.h>
#include <stdlib.h>
#ifndef va_start
	#include <varargs.h>
#endif

typedef std::codecvt<wchar_t, char, mbstate_t> SSCodeCvt;

inline PWSTR StdCodeCvt(PWSTR pDstW, int nDst, PCSTR pSrcA, int nSrc,
    const std::locale& loc=std::locale())
{
    ASSERT(0 != pSrcA);
    ASSERT(0 != pDstW);

	pDstW[0]					= '\0';	

	if ( nSrc > 0 )
	{
		PCSTR pNextSrcA			= pSrcA;
		PWSTR pNextDstW			= pDstW;
		SSCodeCvt::result res	= SSCodeCvt::ok;
		const SSCodeCvt& conv	= SS_USE_FACET(loc, SSCodeCvt);
		SSCodeCvt::state_type st= { 0 };
		res						= conv.in(st,
									pSrcA, pSrcA + nSrc, pNextSrcA,
									pDstW, pDstW + nDst, pNextDstW);

		ASSERT(SSCodeCvt::ok == res);
		ASSERT(SSCodeCvt::error != res);
		ASSERT(pNextDstW >= pDstW);
		ASSERT(pNextSrcA >= pSrcA);

		// Null terminate the converted string

		if ( pNextDstW - pDstW > nDst )
			*(pDstW + nDst) = '\0';
		else
			*pNextDstW = '\0';
	}
    return pDstW;
}
inline PWSTR StdCodeCvt(PWSTR pDstW, int nDst, PCUSTR pSrcA, int nSrc,
    const std::locale& loc=std::locale())
{
    return StdCodeCvt(pDstW, nDst, (PCSTR)pSrcA, nSrc, loc);
}

inline PSTR StdCodeCvt(PSTR pDstA, int nDst, PCWSTR pSrcW, int nSrc,
    const std::locale& loc=std::locale())
{
    ASSERT(0 != pDstA);
    ASSERT(0 != pSrcW);

	pDstA[0]					= '\0';	

	if ( nSrc > 0 )
	{
		PSTR pNextDstA			= pDstA;
		PCWSTR pNextSrcW		= pSrcW;
		SSCodeCvt::result res	= SSCodeCvt::ok;
		const SSCodeCvt& conv	= SS_USE_FACET(loc, SSCodeCvt);
		SSCodeCvt::state_type st= { 0 };
		res						= conv.out(st,
									pSrcW, pSrcW + nSrc, pNextSrcW,
									pDstA, pDstA + nDst, pNextDstA);

		ASSERT(SSCodeCvt::error != res);
		ASSERT(SSCodeCvt::ok == res);	// strict, comment out for sanity
		ASSERT(pNextDstA >= pDstA);
		ASSERT(pNextSrcW >= pSrcW);

		if ( pNextDstA - pDstA > nDst )
			*(pDstA + nDst) = '\0';
		else
			*pNextDstA = '\0';
	}
    return pDstA;
}
inline PUSTR StdCodeCvt(PUSTR pDstA, int nDst, PCWSTR pSrcW, int nSrc,
    const std::locale& loc=std::locale())
{
    return (PUSTR)StdCodeCvt((PSTR)pDstA, nDst, pSrcW, nSrc, loc);
}

#if defined(SS_ALLOCA) && !defined SS_NO_CONVERSION

    #include <malloc.h>	

    #ifdef _CONVERSION_USES_THREAD_LOCALE

	    #ifndef _DEBUG
		    #define SSCVT int _cvt; _cvt; UINT _acp=GetACP(); \
			    _acp; PCWSTR _pw; _pw; PCSTR _pa; _pa
	    #else
		    #define SSCVT int _cvt = 0; _cvt; UINT _acp=GetACP();\
			     _acp; PCWSTR _pw=0; _pw; PCSTR _pa=0; _pa
	    #endif
	    #define SSA2W(pa) (\
		    ((_pa = pa) == 0) ? 0 : (\
			    _cvt = (sslen(_pa)),\
			    StdCodeCvt((PWSTR) _alloca((_cvt+1)*2), (_cvt+1)*2, \
							_pa, _cvt, _acp)))
	    #define SSW2A(pw) (\
		    ((_pw = pw) == 0) ? 0 : (\
			    _cvt = sslen(_pw), \
			    StdCodeCvt((LPSTR) _alloca((_cvt+1)*2), (_cvt+1)*2, \
					_pw, _cvt, _acp)))
	#else

	    #ifndef _DEBUG
		    #define SSCVT int _cvt; _cvt; UINT _acp=CP_ACP; _acp;\
			     PCWSTR _pw; _pw; PCSTR _pa; _pa
	    #else
		    #define SSCVT int _cvt = 0; _cvt; UINT _acp=CP_ACP; \
			    _acp; PCWSTR _pw=0; _pw; PCSTR _pa=0; _pa
	    #endif
	    #define SSA2W(pa) (\
		    ((_pa = pa) == 0) ? 0 : (\
			    _cvt = (sslen(_pa)),\
			    StdCodeCvt((PWSTR) _alloca((_cvt+1)*2), (_cvt+1)*2, \
					_pa, _cvt)))
	    #define SSW2A(pw) (\
		    ((_pw = pw) == 0) ? 0 : (\
			    _cvt = (sslen(_pw)),\
			    StdCodeCvt((LPSTR) _alloca((_cvt+1)*2), (_cvt+1)*2, \
					_pw, _cvt)))
    #endif

    #define SSA2CW(pa) ((PCWSTR)SSA2W((pa)))
    #define SSW2CA(pw) ((PCSTR)SSW2A((pw)))

    #ifdef UNICODE
	    #define SST2A	SSW2A
	    #define SSA2T	SSA2W
	    #define SST2CA	SSW2CA
	    #define SSA2CT	SSA2CW
	    inline PWSTR	SST2W(PTSTR p)			{ return p; }
	    inline PTSTR	SSW2T(PWSTR p)			{ return p; }
	    inline PCWSTR	SST2CW(PCTSTR p)		{ return p; }
	    inline PCTSTR	SSW2CT(PCWSTR p)		{ return p; }
    #else
	    #define SST2W	SSA2W
	    #define SSW2T	SSW2A
	    #define SST2CW	SSA2CW
	    #define SSW2CT	SSW2CA
	    inline PSTR		SST2A(PTSTR p)			{ return p; }
	    inline PTSTR	SSA2T(PSTR p)			{ return p; }
	    inline PCSTR	SST2CA(PCTSTR p)		{ return p; }
	    inline PCTSTR	SSA2CT(PCSTR p)			{ return p; }
    #endif // #ifdef UNICODE

    #if defined(UNICODE)
    // in these cases the default (TCHAR) is the same as OLECHAR
	    inline PCOLESTR	SST2COLE(PCTSTR p)		{ return p; }
	    inline PCTSTR	SSOLE2CT(PCOLESTR p)	{ return p; }
	    inline POLESTR	SST2OLE(PTSTR p)		{ return p; }
	    inline PTSTR	SSOLE2T(POLESTR p)		{ return p; }
    #elif defined(OLE2ANSI)
    // in these cases the default (TCHAR) is the same as OLECHAR
	    inline PCOLESTR	SST2COLE(PCTSTR p)		{ return p; }
	    inline PCTSTR	SSOLE2CT(PCOLESTR p)	{ return p; }
	    inline POLESTR	SST2OLE(PTSTR p)		{ return p; }
	    inline PTSTR	SSOLE2T(POLESTR p)		{ return p; }
    #else
	    //CharNextW doesn't work on Win95 so we use this
	    #define SST2COLE(pa)	SSA2CW((pa))
	    #define SST2OLE(pa)		SSA2W((pa))
	    #define SSOLE2CT(po)	SSW2CA((po))
	    #define SSOLE2T(po)		SSW2A((po))
    #endif

    #ifdef OLE2ANSI
	    #define SSW2OLE		SSW2A
	    #define SSOLE2W		SSA2W
	    #define SSW2COLE	SSW2CA
	    #define SSOLE2CW	SSA2CW
	    inline POLESTR		SSA2OLE(PSTR p)		{ return p; }
	    inline PSTR			SSOLE2A(POLESTR p)	{ return p; }
	    inline PCOLESTR		SSA2COLE(PCSTR p)	{ return p; }
	    inline PCSTR		SSOLE2CA(PCOLESTR p){ return p; }
    #else
	    #define SSA2OLE		SSA2W
	    #define SSOLE2A		SSW2A
	    #define SSA2COLE	SSA2CW
	    #define SSOLE2CA	SSW2CA
	    inline POLESTR		SSW2OLE(PWSTR p)	{ return p; }
	    inline PWSTR		SSOLE2W(POLESTR p)	{ return p; }
	    inline PCOLESTR		SSW2COLE(PCWSTR p)	{ return p; }
	    inline PCWSTR		SSOLE2CW(PCOLESTR p){ return p; }
    #endif

    // Above we've defined macros that look like MS' but all have
    // an 'SS' prefix.  Now we need the real macros.  We'll either
    // get them from the macros above or from MFC/ATL. 

	#if defined (USES_CONVERSION)

		#define _NO_STDCONVERSION	// just to be consistent

	#else

		#ifdef _MFC_VER

			#include <afxconv.h>
			#define _NO_STDCONVERSION // just to be consistent

		#else

			#define USES_CONVERSION SSCVT
			#define A2CW			SSA2CW
			#define W2CA			SSW2CA
			#define T2A				SST2A
			#define A2T				SSA2T
			#define T2W				SST2W
			#define W2T				SSW2T
			#define T2CA			SST2CA
			#define A2CT			SSA2CT
			#define T2CW			SST2CW
			#define W2CT			SSW2CT
			#define ocslen			sslen
			#define ocscpy			sscpy
			#define T2COLE			SST2COLE
			#define OLE2CT			SSOLE2CT
			#define T2OLE			SST2COLE
			#define OLE2T			SSOLE2CT
			#define A2OLE			SSA2OLE
			#define OLE2A			SSOLE2A
			#define W2OLE			SSW2OLE
			#define OLE2W			SSOLE2W
			#define A2COLE			SSA2COLE
			#define OLE2CA			SSOLE2CA
			#define W2COLE			SSW2COLE
			#define OLE2CW			SSOLE2CW
	
		#endif // #ifdef _MFC_VER
	#endif // #ifndef USES_CONVERSION
#endif // #ifndef SS_NO_CONVERSION

#if !defined(ostring) && !defined(OSTRING_DEFINED)
	typedef std::basic_string<OLECHAR> ostring;
	#define OSTRING_DEFINED
#endif

inline PSTR StdCodeCvt(PSTR pDst, int nDst, PCSTR pSrc, int nSrc)
{
	int nChars = SSMIN(nSrc, nDst);

	if ( nChars > 0 )
	{
		pDst[0]				= '\0';
		std::basic_string<char>::traits_type::copy(pDst, pSrc, nChars);
//		std::char_traits<char>::copy(pDst, pSrc, nChars);
		pDst[nChars]	= '\0';
	}

	return pDst;
}
inline PSTR StdCodeCvt(PSTR pDst, int nDst, PCUSTR pSrc, int nSrc)
{
	return StdCodeCvt(pDst, nDst, (PCSTR)pSrc, nSrc);
}
inline PUSTR StdCodeCvt(PUSTR pDst, int nDst, PCSTR pSrc, int nSrc)
{
	return (PUSTR)StdCodeCvt((PSTR)pDst, nDst, pSrc, nSrc);
}

inline PWSTR StdCodeCvt(PWSTR pDst, int nDst, PCWSTR pSrc, int nSrc)
{
	int nChars = SSMIN(nSrc, nDst);

	if ( nChars > 0 )
	{
		pDst[0]				= '\0';
		std::basic_string<wchar_t>::traits_type::copy(pDst, pSrc, nChars);
		pDst[nChars]	= '\0';
	}

	return pDst;
}

#if !defined(tstring) && !defined(TSTRING_DEFINED)
	typedef std::basic_string<TCHAR> tstring;
	#define TSTRING_DEFINED
#endif

#if defined ( _MSC_VER ) && ( _MSC_VER < 1200 )
	#define Q172398(x) (x).erase()
#else
	#define Q172398(x)
#endif

#ifdef SS_NO_REFCOUNT
	#define SSREF(x) (x).c_str()
#else
	#define SSREF(x) (x)
#endif

template<typename CT> inline int sslen(const CT* pT)
{
	return 0 == pT ? 0 : (int)std::basic_string<CT>::traits_type::length(pT);
}
inline SS_NOTHROW int sslen(const std::string& s)
{
	return static_cast<int>(s.length());
}
inline SS_NOTHROW int sslen(const std::wstring& s)
{
	return static_cast<int>(s.length());
}

template<typename CT>
inline CT sstolower(const CT& t, const std::locale& loc = std::locale())
{
	return std::tolower<CT>(t, loc);
}
template<typename CT>
inline CT sstoupper(const CT& t, const std::locale& loc = std::locale())
{
	return std::toupper<CT>(t, loc);
}

typedef std::string::size_type		SS_SIZETYPE; // just for shorthand, really
typedef std::string::pointer		SS_PTRTYPE;  
typedef std::wstring::size_type		SW_SIZETYPE;
typedef std::wstring::pointer		SW_PTRTYPE;  

inline void	ssasn(std::string& sDst, const std::string& sSrc)
{
	if ( sDst.c_str() != sSrc.c_str() )
	{
		sDst.erase();
		sDst.assign(SSREF(sSrc));
	}
}
inline void	ssasn(std::string& sDst, PCSTR pA)
{

	if ( 0 == pA )
	{
		sDst.erase();
	}

	else if ( pA >= sDst.c_str() && pA <= sDst.c_str() + sDst.size() )
	{
		sDst =sDst.substr(static_cast<SS_SIZETYPE>(pA-sDst.c_str()));
	}

	else
	{
		Q172398(sDst);
		sDst.assign(pA);
	}
}
inline void	ssasn(std::string& sDst, const std::wstring& sSrc)
{
	if ( sSrc.empty() )
	{
		sDst.erase();
	}
	else
	{
		int nDst	= static_cast<int>(sSrc.size());

#ifdef SS_MBCS
		nDst	= static_cast<int>(static_cast<double>(nDst) * 1.3);
#endif

		sDst.resize(nDst+1);
		PCSTR szCvt = StdCodeCvt(const_cast<SS_PTRTYPE>(sDst.data()), nDst,
			sSrc.c_str(), static_cast<int>(sSrc.size()));

#ifdef SS_MBCS
		sDst.resize(sslen(szCvt));
#else
		szCvt;
		sDst.resize(sSrc.size());
#endif
	}
}
inline void	ssasn(std::string& sDst, PCWSTR pW)
{
	int nSrc	= sslen(pW);
	if ( nSrc > 0 )
	{
		int nSrc	= sslen(pW);
		int nDst	= nSrc;

#ifdef SS_MBCS
		nDst	= static_cast<int>(static_cast<double>(nDst) * 1.3);
#endif

		sDst.resize(nDst + 1);
		PCSTR szCvt = StdCodeCvt(const_cast<SS_PTRTYPE>(sDst.data()), nDst,
			pW, nSrc);

#ifdef SS_MBCS
		sDst.resize(sslen(szCvt));
#else
		sDst.resize(nDst);
		szCvt;
#endif
	}
	else
	{
		sDst.erase();
	}
}
inline void ssasn(std::string& sDst, const int nNull)
{
	UNUSED(nNull);
	ASSERT(nNull==0);
	sDst.assign("");
}	
inline void	ssasn(std::wstring& sDst, const std::wstring& sSrc)
{
	if ( sDst.c_str() != sSrc.c_str() )
	{
		sDst.erase();
		sDst.assign(SSREF(sSrc));
	}
}
inline void	ssasn(std::wstring& sDst, PCWSTR pW)
{
	if ( 0 == pW )
	{
		sDst.erase();
	}

	else if ( pW >= sDst.c_str() && pW <= sDst.c_str() + sDst.size() )
	{
		sDst = sDst.substr(static_cast<SW_SIZETYPE>(pW-sDst.c_str()));
	}
	else
	{
		Q172398(sDst);
		sDst.assign(pW);
	}
}
#undef StrSizeType
inline void	ssasn(std::wstring& sDst, const std::string& sSrc)
{
	if ( sSrc.empty() )
	{
		sDst.erase();
	}
	else
	{
		int nSrc	= static_cast<int>(sSrc.size());
		int nDst	= nSrc;

		sDst.resize(nSrc+1);
		PCWSTR szCvt = StdCodeCvt(const_cast<SW_PTRTYPE>(sDst.data()), nDst,
			sSrc.c_str(), nSrc);

		sDst.resize(sslen(szCvt));
	}
}
inline void	ssasn(std::wstring& sDst, PCSTR pA)
{
	int nSrc	= sslen(pA);

	if ( 0 == nSrc )
	{
		sDst.erase();
	}
	else
	{
		int nDst	= nSrc;
		sDst.resize(nDst+1);
		PCWSTR szCvt = StdCodeCvt(const_cast<SW_PTRTYPE>(sDst.data()), nDst, pA,
			nSrc);

		sDst.resize(sslen(szCvt));
	}
}
inline void ssasn(std::wstring& sDst, const int nNull)
{
	UNUSED(nNull);
	ASSERT(nNull==0);
	sDst.assign(L"");
}

inline void	ssadd(std::string& sDst, const std::wstring& sSrc)
{
	int nSrc	= static_cast<int>(sSrc.size());

	if ( nSrc > 0 )
	{
		int nDst	= static_cast<int>(sDst.size());
		int nAdd	= nSrc;

#ifdef SS_MBCS
		nAdd		= static_cast<int>(static_cast<double>(nAdd) * 1.3);
#endif

		sDst.resize(nDst+nAdd+1);
		PCSTR szCvt = StdCodeCvt(const_cast<SS_PTRTYPE>(sDst.data()+nDst),
			nAdd, sSrc.c_str(), nSrc);

#ifdef SS_MBCS
		sDst.resize(nDst + sslen(szCvt));
#else
		sDst.resize(nDst + nAdd);
		szCvt;
#endif
	}
}
inline void	ssadd(std::string& sDst, const std::string& sSrc)
{
	sDst += sSrc;
}
inline void	ssadd(std::string& sDst, PCWSTR pW)
{
	int nSrc		= sslen(pW);
	if ( nSrc > 0 )
	{
		int nDst	= static_cast<int>(sDst.size());
		int nAdd	= nSrc;

#ifdef SS_MBCS
		nAdd	= static_cast<int>(static_cast<double>(nAdd) * 1.3);
#endif

		sDst.resize(nDst + nAdd + 1);
		PCSTR szCvt = StdCodeCvt(const_cast<SS_PTRTYPE>(sDst.data()+nDst),
			nAdd, pW, nSrc);

#ifdef SS_MBCS
		sDst.resize(nDst + sslen(szCvt));
#else
		sDst.resize(nDst + nSrc);
		szCvt;
#endif
	}
}
inline void	ssadd(std::string& sDst, PCSTR pA)
{
	if ( pA )
	{
		if ( pA >= sDst.c_str() && pA <= sDst.c_str()+sDst.length())
		{
			if ( sDst.capacity() <= sDst.size()+sslen(pA) )
				sDst.append(std::string(pA));
			else
				sDst.append(pA);
		}
		else
		{
			sDst.append(pA); 
		}
	}
}
inline void	ssadd(std::wstring& sDst, const std::wstring& sSrc)
{
	sDst += sSrc;
}
inline void	ssadd(std::wstring& sDst, const std::string& sSrc)
{
	if ( !sSrc.empty() )
	{
		int nSrc	= static_cast<int>(sSrc.size());
		int nDst	= static_cast<int>(sDst.size());

		sDst.resize(nDst + nSrc + 1);
		PCWSTR szCvt = StdCodeCvt(const_cast<SW_PTRTYPE>(sDst.data()+nDst), 
			nSrc + 1, sSrc.c_str(), nSrc);

#ifdef SS_MBCS
		sDst.resize(nDst + sslen(szCvt));
#else
		sDst.resize(nDst + nSrc);
		szCvt;
#endif
	}
}
inline void	ssadd(std::wstring& sDst, PCSTR pA)
{
	int nSrc		= sslen(pA);

	if ( nSrc > 0 )
	{
		int nDst	= static_cast<int>(sDst.size());

		sDst.resize(nDst + nSrc + 1);
		PCWSTR szCvt = StdCodeCvt(const_cast<SW_PTRTYPE>(sDst.data()+nDst),
			nSrc + 1, pA, nSrc);

#ifdef SS_MBCS
		sDst.resize(nDst + sslen(szCvt));
#else
		sDst.resize(nDst + nSrc);
		szCvt;
#endif
	}
}
inline void	ssadd(std::wstring& sDst, PCWSTR pW)
{
	if ( pW )
	{
		if ( pW >= sDst.c_str() && pW <= sDst.c_str()+sDst.length())
		{
			if ( sDst.capacity() <= sDst.size()+sslen(pW) )
				sDst.append(std::wstring(pW));
			else
				sDst.append(pW);
		}
		else
		{
			sDst.append(pW);
		}
	}
}

template<typename CT>
inline int sscmp(const CT* pA1, const CT* pA2)
{
    CT f;
    CT l;

    do 
    {
	    f = *(pA1++);
	    l = *(pA2++);
    } while ( (f) && (f == l) );

    return (int)(f - l);
}

template<typename CT>
inline int ssicmp(const CT* pA1, const CT* pA2)
{
	std::locale loc = std::locale::classic();
    const std::ctype<CT>& ct = SS_USE_FACET(loc, std::ctype<CT>);
    CT f;
    CT l;

    do 
    {
	    f = ct.tolower(*(pA1++));
	    l = ct.tolower(*(pA2++));
    } while ( (f) && (f == l) );

    return (int)(f - l);
}

template<typename CT>
inline void sslwr(CT* pT, size_t nLen, const std::locale& loc=std::locale())
{
	SS_USE_FACET(loc, std::ctype<CT>).tolower(pT, pT+nLen);
}
template<typename CT>
inline void ssupr(CT* pT, size_t nLen, const std::locale& loc=std::locale())
{
	SS_USE_FACET(loc, std::ctype<CT>).toupper(pT, pT+nLen);
}

	inline int ssvsprintf(PSTR pA, size_t nCount, PCSTR pFmtA, va_list vl)
	{
      return vsprintf_s(pA, nCount, pFmtA, vl);
	}

	inline int ssvsprintf(PWSTR pW, size_t nCount, PCWSTR pFmtW, va_list vl)
	{
      return _vstprintf(pW, nCount, pFmtW, vl);
	}

#if defined (SS_WIN32) && !defined(SS_ANSI)
	inline int ssload(HMODULE hInst, UINT uId, PSTR pBuf, int nMax)
	{
		return ::LoadStringA(hInst, uId, pBuf, nMax);
	}
	inline int ssload(HMODULE hInst, UINT uId, PWSTR pBuf, int nMax)
	{
		return ::LoadStringW(hInst, uId, pBuf, nMax);
	}
#endif

template <typename CT>
inline int sscoll(const CT* sz1, int nLen1, const CT* sz2, int nLen2)
{
	const std::collate<CT>& coll =
		SS_USE_FACET(std::locale(), std::collate<CT>);

	return coll.compare(sz2, sz2+nLen2, sz1, sz1+nLen1);
}
template <typename CT>
inline int ssicoll(const CT* sz1, int nLen1, const CT* sz2, int nLen2)
{
	const std::locale loc;
	const std::collate<CT>& coll = SS_USE_FACET(loc, std::collate<CT>);
	const std::basic_string<CT> sEmpty;
    std::basic_string<CT> s1(sz1 ? sz1 : sEmpty.c_str());
    std::basic_string<CT> s2(sz2 ? sz2 : sEmpty.c_str());

	sslwr(const_cast<CT*>(s1.c_str()), nLen1, loc);
	sslwr(const_cast<CT*>(s2.c_str()), nLen2, loc);
	return coll.compare(s2.c_str(), s2.c_str()+nLen2,
						s1.c_str(), s1.c_str()+nLen1);
}

#if defined (SS_WIN32) && !defined(SS_ANSI)
	inline DWORD ssfmtmsg(DWORD dwFlags, LPCVOID pSrc, DWORD dwMsgId,
						  DWORD dwLangId, PSTR pBuf, DWORD nSize,
						  va_list* vlArgs)
	{ 
		return FormatMessageA(dwFlags, pSrc, dwMsgId, dwLangId,
							  pBuf, nSize,vlArgs);
	}
	inline DWORD ssfmtmsg(DWORD dwFlags, LPCVOID pSrc, DWORD dwMsgId,
						  DWORD dwLangId, PWSTR pBuf, DWORD nSize,
						  va_list* vlArgs)
	{
		return FormatMessageW(dwFlags, pSrc, dwMsgId, dwLangId,
							  pBuf, nSize,vlArgs);
	}
#else
#endif
 
template<typename CT1, typename CT2>
inline int sscpycvt(CT1* pDst, const CT2* pSrc, int nMax)
{
	int nSrc = sslen(pSrc);
	const CT1* szCvt = StdCodeCvt(pDst, nMax, pSrc, nSrc);
	return sslen(szCvt);
}

inline int sscpycvt(PSTR pDst, PCSTR pSrc, int nMax)
{
	int nCount = nMax;
	for (; nCount > 0 && *pSrc; ++pSrc, ++pDst, --nCount)
		std::basic_string<char>::traits_type::assign(*pDst, *pSrc);

	*pDst =  '\0';
	return nMax - nCount;
}
inline int sscpycvt(PWSTR pDst, PCWSTR pSrc, int nMax)
{
	int nCount = nMax;
	for (; nCount > 0 && *pSrc; ++pSrc, ++pDst, --nCount)
		std::basic_string<wchar_t>::traits_type::assign(*pDst, *pSrc);

	*pDst = L'\0';
	return nMax - nCount;
}
inline int sscpycvt(PWSTR pDst, PCSTR pSrc, int nMax)
{
	const PWSTR szCvt = StdCodeCvt(pDst, nMax, pSrc, nMax);
	return sslen(szCvt);
}

template<typename CT1, typename CT2>
inline int sscpy(CT1* pDst, const CT2* pSrc, int nMax, int nLen)
{
	return sscpycvt(pDst, pSrc, SSMIN(nMax, nLen));
}
template<typename CT1, typename CT2>
inline int sscpy(CT1* pDst, const CT2* pSrc, int nMax)
{
	return sscpycvt(pDst, pSrc, SSMIN(nMax, sslen(pSrc)));
}
template<typename CT1, typename CT2>
inline int sscpy(CT1* pDst, const CT2* pSrc)
{
	return sscpycvt(pDst, pSrc, sslen(pSrc));
}
template<typename CT1, typename CT2>
inline int sscpy(CT1* pDst, const std::basic_string<CT2>& sSrc, int nMax)
{
	return sscpycvt(pDst, sSrc.c_str(), SSMIN(nMax, (int)sSrc.length()));
}
template<typename CT1, typename CT2>
inline int sscpy(CT1* pDst, const std::basic_string<CT2>& sSrc)
{
	return sscpycvt(pDst, sSrc.c_str(), (int)sSrc.length());
}

#ifdef SS_INC_COMDEF
	template<typename CT1>
	inline int sscpy(CT1* pDst, const _bstr_t& bs, int nMax)
	{
		return sscpycvt(pDst, static_cast<PCOLESTR>(bs),
            SSMIN(nMax, static_cast<int>(bs.length())));
	}
	template<typename CT1>
	inline int sscpy(CT1* pDst, const _bstr_t& bs)
	{
		return sscpy(pDst, bs, static_cast<int>(bs.length()));
	}
#endif

template<typename CT>
struct SSToUpper : public std::binary_function<CT, std::locale, CT>
{
    inline CT operator()(const CT& t, const std::locale& loc) const
    {
	    return sstoupper<CT>(t, loc);
    }
};
template<typename CT>
struct SSToLower : public std::binary_function<CT, std::locale, CT>
{
    inline CT operator()(const CT& t, const std::locale& loc) const
    {
	    return sstolower<CT>(t, loc);
    }
};

template<typename CT>
struct NotSpace : public std::unary_function<CT, bool>
{  
	const std::locale loc;
	NotSpace(const std::locale& locArg=std::locale()) : loc(locArg) {}
	bool operator() (CT t) const { return !std::isspace(t, loc); }
};

template<typename ARG>
struct FmtArg
{
    explicit FmtArg(const ARG& arg) : a_(arg) {}
    const ARG& operator()() const { return a_; }
    const ARG& a_;
private:
    FmtArg& operator=(const FmtArg&) { return *this; }
};

template<typename CT>
class CStdStr : public std::basic_string<CT>
{
	
	#define MYBASE std::basic_string<CT>				 // my base class	
	typedef CStdStr<CT>							MYTYPE;	 // myself
	typedef typename MYBASE::const_pointer		PCMYSTR; // PCSTR or PCWSTR 
	typedef typename MYBASE::pointer			PMYSTR;	 // PSTR or PWSTR
	typedef typename MYBASE::iterator			MYITER;  // my iterator type
	typedef typename MYBASE::const_iterator		MYCITER; // you get the idea...
	typedef typename MYBASE::reverse_iterator	MYRITER;
	typedef typename MYBASE::size_type			MYSIZE;   
	typedef typename MYBASE::value_type			MYVAL; 
	typedef typename MYBASE::allocator_type		MYALLOC;
	
public:
	// shorthand conversion from PCTSTR to string resource ID
	#define SSRES(pctstr)  LOWORD(reinterpret_cast<unsigned long>(pctstr))	

	bool TryLoad(const void* pT)
	{
		bool bLoaded = false;

#if defined(SS_WIN32) && !defined(SS_ANSI)
		if ( ( pT != NULL ) && SS_IS_INTRESOURCE(pT) )
		{
			UINT nId = LOWORD(reinterpret_cast<unsigned long>(pT));
			if ( !LoadString(nId) )
			{
				TRACE(PLATFORM_STRING("Can't load string %u\n"), SSRES(pT));
			}
			bLoaded = true;
		}
#endif

		return bLoaded;
	}


	// CStdStr inline constructors
	CStdStr()
	{
	}

	CStdStr(const MYTYPE& str) : MYBASE(SSREF(str))
	{
	}

	CStdStr(const std::string& str)
	{
		ssasn(*this, SSREF(str));
	}

	CStdStr(const std::wstring& str)
	{
		ssasn(*this, SSREF(str));
	}

	CStdStr(PCMYSTR pT, MYSIZE n) : MYBASE(pT, n)
	{
	}

#ifdef SS_UNSIGNED
	CStdStr(PCUSTR pU)
	{
		*this = reinterpret_cast<PCSTR>(pU);
	}
#endif

	CStdStr(PCSTR pA)
	{
	#ifdef SS_ANSI
		*this = pA;
	#else
		if ( !TryLoad(pA) )
			*this = pA;
	#endif
	}

	CStdStr(PCWSTR pW)
	{
	#ifdef SS_ANSI
		*this = pW;
	#else
		if ( !TryLoad(pW) )
			*this = pW;
	#endif
	}

	CStdStr(MYCITER first, MYCITER last)
		: MYBASE(first, last)
	{
	}

	CStdStr(MYSIZE nSize, MYVAL ch, const MYALLOC& al=MYALLOC())
		: MYBASE(nSize, ch, al)
	{
	}

	#ifdef SS_INC_COMDEF
		CStdStr(const _bstr_t& bstr)
		{
			if ( bstr.length() > 0 )
				this->append(static_cast<PCMYSTR>(bstr), bstr.length());
		}
	#endif

	MYTYPE& operator=(const MYTYPE& str)
	{ 
		ssasn(*this, str); 
		return *this;
	}

	MYTYPE& operator=(const std::string& str)
	{
		ssasn(*this, str);
		return *this;
	}

	MYTYPE& operator=(const std::wstring& str)
	{
		ssasn(*this, str);
		return *this;
	}

	MYTYPE& operator=(PCSTR pA)
	{
		ssasn(*this, pA);
		return *this;
	}

	MYTYPE& operator=(PCWSTR pW)
	{
		ssasn(*this, pW);
		return *this;
	}

#ifdef SS_UNSIGNED
	MYTYPE& operator=(PCUSTR pU)
	{
		ssasn(*this, reinterpret_cast<PCSTR>(pU));
		return *this;
	}
#endif

	MYTYPE& operator=(CT t)
	{
		Q172398(*this);
		this->assign(1, t);
		return *this;
	}

	#ifdef SS_INC_COMDEF
		MYTYPE& operator=(const _bstr_t& bstr)
		{
			if ( bstr.length() > 0 )
			{
				this->assign(static_cast<PCMYSTR>(bstr), bstr.length());
				return *this;
			}
			else
			{
				this->erase();
				return *this;
			}
		}
	#endif

	#if ( defined(_MSC_VER) && ( _MSC_VER < 1200 ) ) || defined(SS_NO_REFCOUNT) 

		MYTYPE& assign(const MYTYPE& str)
		{
			Q172398(*this);
			sscpy(GetBuffer(str.size()+1), SSREF(str));
			this->ReleaseBuffer(str.size());
			return *this;
		}

		MYTYPE& assign(const MYTYPE& str, MYSIZE nStart, MYSIZE nChars)
		{
			nChars		= SSMIN(nChars, str.length() - nStart);
			MYTYPE strTemp(str.c_str()+nStart, nChars);
			Q172398(*this);
			this->assign(strTemp);
			return *this;
		}

		MYTYPE& assign(const MYBASE& str)
		{
			ssasn(*this, str);
			return *this;
		}

		MYTYPE& assign(const MYBASE& str, MYSIZE nStart, MYSIZE nChars)
		{
			// This overload of basic_string::assign is supposed to assign up to
			// <nChars> or the NULL terminator, whichever comes first.  Since we
			// are about to call a less forgiving overload (in which <nChars>
			// must be a valid length), we must adjust the length here to a safe
			// value. Thanks to Ullrich Poll�hne for catching this bug

			nChars		= SSMIN(nChars, str.length() - nStart);

			// Watch out for assignment to self

			if ( this == &str )
			{
				MYTYPE strTemp(str.c_str() + nStart, nChars);
				static_cast<MYBASE*>(this)->assign(strTemp);
			}
			else
			{
				Q172398(*this);
				static_cast<MYBASE*>(this)->assign(str.c_str()+nStart, nChars);
			}
			return *this;
		}

		MYTYPE& assign(const CT* pC, MYSIZE nChars)
		{
			// Q172398 only fix -- erase before assigning, but not if we're
			// assigning from our own buffer

	#if defined ( _MSC_VER ) && ( _MSC_VER < 1200 )
			if ( !this->empty() &&
				( pC < this->data() || pC > this->data() + this->capacity() ) )
			{
				this->erase();
			}
	#endif
			Q172398(*this);
			static_cast<MYBASE*>(this)->assign(pC, nChars);
			return *this;
		}

		MYTYPE& assign(MYSIZE nChars, MYVAL val)
		{
			Q172398(*this);
			static_cast<MYBASE*>(this)->assign(nChars, val);
			return *this;
		}

		MYTYPE& assign(const CT* pT)
		{
			return this->assign(pT, MYBASE::traits_type::length(pT));
		}

		MYTYPE& assign(MYCITER iterFirst, MYCITER iterLast)
		{
	#if defined ( _MSC_VER ) && ( _MSC_VER < 1200 ) 
			// Q172398 fix.  don't call erase() if we're assigning from ourself
			if ( iterFirst < this->begin() ||
                 iterFirst > this->begin() + this->size() )
            {
				this->erase()
            }
	#endif
			this->replace(this->begin(), this->end(), iterFirst, iterLast);
			return *this;
		}
	#endif

	MYTYPE& operator+=(const MYTYPE& str)
	{
		ssadd(*this, str);
		return *this;
	}

	MYTYPE& operator+=(const std::string& str)
	{
		ssadd(*this, str);
		return *this; 
	}

	MYTYPE& operator+=(const std::wstring& str)
	{
		ssadd(*this, str);
		return *this;
	}

	MYTYPE& operator+=(PCSTR pA)
	{
		ssadd(*this, pA);
		return *this;
	}

	MYTYPE& operator+=(PCWSTR pW)
	{
		ssadd(*this, pW);
		return *this;
	}

	MYTYPE& operator+=(CT t)
	{
		this->append(1, t);
		return *this;
	}
	#ifdef SS_INC_COMDEF	// if we have _bstr_t, define a += for it too.
		MYTYPE& operator+=(const _bstr_t& bstr)
		{
			return this->operator+=(static_cast<PCMYSTR>(bstr));
		}
	#endif

    MYTYPE& ToUpper(const std::locale& loc=std::locale())
	{
		std::transform(this->begin(),
					   this->end(),
					   this->begin(),
				   std::bind2nd(SSToUpper<CT>(), loc));

		return *this;
	}

	MYTYPE& ToLower(const std::locale& loc=std::locale())
	{
		if ( !empty() )
		{
			sslwr(this->GetBuf(), this->size(), loc);
			this->RelBuf();
		}
		return *this;
	}

	MYTYPE& Normalize()
	{
		return Trim().ToLower();
	}

	CT* GetBuf(int nMinLen=-1)
	{
		if ( static_cast<int>(this->size()) < nMinLen )
			this->resize(static_cast<MYSIZE>(nMinLen));

		return this->empty() ? const_cast<CT*>(this->data()) : &(this->at(0));
	}

	CT* SetBuf(MYSIZE nLen)
	{
		nLen = ( nLen > 0 ? nLen : 0 );
		if ( this->capacity() < 1 && nLen == 0 )
			this->resize(1);

		this->resize(static_cast<MYSIZE>(nLen));
		return const_cast<CT*>(this->data());
	}
	void RelBuf(int nNewLen=-1)
	{
		this->resize(static_cast<MYSIZE>(nNewLen > -1 ? nNewLen :
                                                        sslen(this->c_str())));
	}

	void BufferRel()		 { RelBuf(); }			// backwards compatability
	CT*  Buffer()			 { return GetBuf(); }	// backwards compatability
	CT*  BufferSet(int nLen) { return SetBuf(nLen);}// backwards compatability

	bool Equals(const CT* pT, bool bUseCase=false) const
	{
      if (bUseCase)
      {
         return this->compare(pT) == 0;
      }
      else
      {
         return _wcsicmp(c_str(), pT) == 0;
      }
	} 

#ifndef SS_ANSI

	bool Load(UINT nId, HMODULE hModule=NULL)
	{
		bool bLoaded		= false;	// set to true of we succeed.

	#ifdef _MFC_VER		// When in Rome (or MFC land)...

		HMODULE hModuleOld = NULL;

		if ( NULL != hModule )
		{
			hModuleOld = AfxGetResourceHandle();
			AfxSetResourceHandle(hModule);
		}

		// ...load the string

		CString strRes;
		bLoaded				= FALSE != strRes.LoadString(nId);

		// ...and if we set the resource handle, restore it.

		if ( NULL != hModuleOld )
			AfxSetResourceHandle(hModule);

		if ( bLoaded )
			*this			= strRes;

	#else // otherwise make our own hackneyed version of CString's Load
		
		// Get the resource name and module handle

		if ( NULL == hModule )
			hModule			= GetResourceHandle();

		PCTSTR szName		= MAKEINTRESOURCE((nId>>4)+1); // lifted 
		DWORD dwSize		= 0;

		// No sense continuing if we can't find the resource

		HRSRC hrsrc			= ::FindResource(hModule, szName, RT_STRING);

		if ( NULL == hrsrc )
		{
			TRACE(PLATFORM_STRING("Cannot find resource %d: 0x%X"), nId, ::GetLastError());
		}
		else if ( 0 == (dwSize = ::SizeofResource(hModule, hrsrc) / sizeof(CT)))
		{
			TRACE(PLATFORM_STRING("Cant get size of resource %d 0x%X\n"),nId,GetLastError());
		}
		else
		{
			bLoaded			= 0 != ssload(hModule, nId, GetBuf(dwSize), dwSize);
			ReleaseBuffer();
		}

	#endif  // #ifdef _MFC_VER

		if ( !bLoaded )
			TRACE(PLATFORM_STRING("String not loaded 0x%X\n"), ::GetLastError());

		return bLoaded;
	}

#endif  // #ifdef SS_ANSI
	 
#ifdef SS_SAFE_FORMAT       
	void Fmt(const CT* szFmt, ...)
	{
		va_list argList;
		va_start(argList, szFmt);
		FormatV(szFmt, argList);
		va_end(argList);
	}

#ifndef SS_ANSI

    void Format(UINT nId)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) ) 
            this->swap(strFmt);
    }
    template<class A1>
    void Format(UINT nId, const A1& v)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
            Fmt(strFmt, FmtArg<A1>(v)());
    }
    template<class A1, class A2>
    void Format(UINT nId, const A1& v1, const A2& v2)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
           Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)());
    }
    template<class A1, class A2, class A3>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)());
        }
    }
    template<class A1, class A2, class A3, class A4>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(),FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(),FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
           Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(),FmtArg<A10>(v10)(),FmtArg<A11>(v11)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)(), FmtArg<A13>(v13)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)(), FmtArg<A13>(v13)(),FmtArg<A14>(v14)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
                FmtArg<A15>(v15)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15, class A16>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15,
                const A16& v16)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
                FmtArg<A15>(v15)(), FmtArg<A16>(v16)());
        }
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15, class A16, class A17>
    void Format(UINT nId, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15,
                const A16& v16, const A17& v17)
    {
		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
        {
            Fmt(strFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
                FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
                FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
                FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
                FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
                FmtArg<A15>(v15)(),FmtArg<A16>(v16)(),FmtArg<A17>(v17)());
        }
    }
    
#endif // #ifndef SS_ANSI

    // ...now the other overload of Format: the one that takes a string literal

    void Format(const CT* szFmt)
    {
        *this = szFmt;
    }
    template<class A1>
    void Format(const CT* szFmt, const A1& v)
    {
       A1 a = FmtArg<A1>(v)();

        Fmt(szFmt, a);
    }
    template<class A1, class A2>
    void Format(const CT* szFmt, const A1& v1, const A2& v2)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)());
    }
    template<class A1, class A2, class A3>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)());
    }
    template<class A1, class A2, class A3, class A4>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)());
    }
    template<class A1, class A2, class A3, class A4, class A5>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(),FmtArg<A10>(v10)(),FmtArg<A11>(v11)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)(), FmtArg<A13>(v13)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)(), FmtArg<A13>(v13)(),FmtArg<A14>(v14)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
            FmtArg<A15>(v15)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15, class A16>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15,
                const A16& v16)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
            FmtArg<A15>(v15)(), FmtArg<A16>(v16)());
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
        class A7, class A8, class A9, class A10, class A11, class A12,
        class A13, class A14, class A15, class A16, class A17>
    void Format(const CT* szFmt, const A1& v1, const A2& v2, const A3& v3,
                const A4& v4, const A5& v5, const A6& v6, const A7& v7,
                const A8& v8, const A9& v9, const A10& v10, const A11& v11,
                const A12& v12, const A13& v13, const A14& v14, const A15& v15,
                const A16& v16, const A17& v17)
    {
        Fmt(szFmt, FmtArg<A1>(v1)(), FmtArg<A2>(v2)(),
            FmtArg<A3>(v3)(), FmtArg<A4>(v4)(), FmtArg<A5>(v5)(),
            FmtArg<A6>(v6)(), FmtArg<A7>(v7)(), FmtArg<A8>(v8)(),
            FmtArg<A9>(v9)(), FmtArg<A10>(v10)(),FmtArg<A11>(v11)(),
            FmtArg<A12>(v12)(),FmtArg<A13>(v13)(),FmtArg<A14>(v14)(),
            FmtArg<A15>(v15)(),FmtArg<A16>(v16)(),FmtArg<A17>(v17)());
    }

#else  // #ifdef SS_SAFE_FORMAT


#ifndef SS_ANSI

	void Format(UINT nId, ...)
	{
		va_list argList;
		va_start(argList, nId);

		MYTYPE strFmt;
		if ( strFmt.Load(nId) )
			FormatV(strFmt, argList);

		va_end(argList);
	}
    
#endif  // #ifdef SS_ANSI

	void Format(const CT* szFmt, ...)
	{
		va_list argList;
		va_start(argList, szFmt);
		FormatV(szFmt, argList);
		va_end(argList);
	}

#endif // #ifdef SS_SAFE_FORMAT

	void AppendFormat(const CT* szFmt, ...)
	{
		va_list argList;
		va_start(argList, szFmt);
		AppendFormatV(szFmt, argList);
		va_end(argList);
	}

	#define MAX_FMT_TRIES		5	 // #of times we try 
	#define FMT_BLOCK_SIZE		2048 // # of bytes to increment per try
	#define BUFSIZE_1ST	256
	#define BUFSIZE_2ND 512
	#define STD_BUF_SIZE		1024

	void AppendFormatV(const CT* szFmt, va_list argList)
	{
		CT szBuf[STD_BUF_SIZE];

		int nLen = ssvsprintf(szBuf, STD_BUF_SIZE, szFmt, argList);

      if ( 0 < nLen )
			this->append(szBuf, nLen);
	}

	void FormatV(const CT* szFormat, va_list argList)
	{
      int nLen	= _vsctprintf((const wchar_t *) szFormat, argList);

		ssvsprintf(GetBuffer(nLen), nLen+1, szFormat, argList);
		ReleaseBuffer();
	}

	BSTR AllocSysString() const
	{
		ostring os;
		ssasn(os, *this);
		return ::SysAllocString(os.c_str());
	}

	int Collate(PCMYSTR szThat) const
	{
		return sscoll(this->c_str(), this->length(), szThat, sslen(szThat));
	}

	int CollateNoCase(PCMYSTR szThat) const
	{
		return ssicoll(this->c_str(), this->length(), szThat, sslen(szThat));
	}

	int Compare(PCMYSTR szThat) const
	{
		return this->compare(szThat);	
	}

	int CompareNoCase(PCMYSTR szThat)	const
	{
		return ssicmp(this->c_str(), szThat);
	}

   bool StartsWith(PCMYSTR szText) const
   {
      int len = sslen(szText);

      if (Left(len).CompareNoCase(szText) == 0)
         return true;
      
      return false;
   }

   bool EndsWith(PCMYSTR szText) const
   {
      int len = sslen(szText);

      if (Right(len).CompareNoCase(szText) == 0)
         return true;

      return false;
   }

	int Delete(int nIdx, int nCount=1)
	{
        if ( nIdx < 0 )
			nIdx = 0;

		if ( nIdx < this->GetLength() )
			this->erase(static_cast<MYSIZE>(nIdx), static_cast<MYSIZE>(nCount));

		return GetLength();
	}

	void Empty()
	{
		this->erase();
	}

	int Find(CT ch) const
	{
		MYSIZE nIdx	= this->find_first_of(ch);
		return static_cast<int>(MYBASE::npos == nIdx  ? -1 : nIdx);
	}

	int Find(PCMYSTR szSub) const
	{
		MYSIZE nIdx	= this->find(szSub);
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

	int Find(CT ch, MYSIZE nStart) const
	{
		MYSIZE nIdx	= this->find_first_of(ch, static_cast<MYSIZE>(nStart));
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

	int Find(PCMYSTR szSub, MYSIZE nStart) const
	{
		MYSIZE nIdx	= this->find(szSub, static_cast<MYSIZE>(nStart));
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

   int FindNoCase(PCMYSTR szSub) const
   {
      MYTYPE sFindIn = this->c_str();
      MYTYPE sLookFor = szSub;

      sFindIn.ToLower();
      sLookFor.ToLower();

      MYSIZE nIdx	= sFindIn.Find(sLookFor);
      return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
   }

   int FindNoCase(PCMYSTR szSub, MYSIZE nStart) const
   {
      MYTYPE sFindIn = this->c_str();
      MYTYPE sLookFor = szSub;

      sFindIn.ToLower();
      sLookFor.ToLower();

      MYSIZE nIdx	= sFindIn.Find(sLookFor, nStart);
      return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
   }

   bool Contains(PCMYSTR szSub) const
   {
      MYTYPE sFindIn = this->c_str();
      MYTYPE sLookFor = szSub;

      if (sFindIn.Find(sLookFor) >= 0)
         return true;
      else
         return false;
   }

   bool ContainsNoCase(PCMYSTR szSub) const
   {
      MYTYPE sFindIn = this->c_str();
      MYTYPE sLookFor = szSub;

      // Convert to lower case so that we'll do the search in 
      // an in-case sensitive manner.
      sFindIn.ToLower();
      sLookFor.ToLower();

      if (sFindIn.Find(sLookFor) >= 0)
         return true;
      else
         return false;
   }

	int FindOneOf(PCMYSTR szCharSet) const
	{
		MYSIZE nIdx = this->find_first_of(szCharSet);
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

   int NumberOf(PCMYSTR needle) const
   {
      int maxLimit = 10000000;
      
      long foundPos = Find(needle);
      long totalCount = 0;

      while (foundPos >= 0 && totalCount < maxLimit)
      {
         totalCount++;

         foundPos = Find(needle, foundPos + 1);
      }

      return totalCount;
   }

	int GetAllocLength()
	{
		return static_cast<int>(this->capacity());
	}

   CT SafeGetAt(unsigned int nIdx) const
   {
      if (nIdx < this->size())
         return this->at(static_cast<MYSIZE>(nIdx));
      else
         return '\0';
   }

	CT GetAt(int nIdx) const
	{
		return this->at(static_cast<MYSIZE>(nIdx));
	}


	CT* GetBuffer(int nMinLen=-1)
	{
		return GetBuf(nMinLen);
	}

	CT* GetBufferSetLength(int nLen)
	{
		return BufferSet(nLen);
	}

	int GetLength() const
	{
		return static_cast<int>(this->length());
	}
	
	int Insert(int nIdx, CT ch)
	{
		if ( static_cast<MYSIZE>(nIdx) > this->size()-1 )
			this->append(1, ch);
		else
			this->insert(static_cast<MYSIZE>(nIdx), 1, ch);

		return GetLength();
	}
	int Insert(int nIdx, PCMYSTR sz)
	{
		if ( static_cast<MYSIZE>(nIdx) >= this->size() )
			this->append(sz, static_cast<MYSIZE>(sslen(sz)));
		else
			this->insert(static_cast<MYSIZE>(nIdx), sz);

		return GetLength();
	}

	bool IsEmpty() const
	{
		return this->empty();
	}

	MYTYPE Left(int nCount) const
	{
        // Range check the count.

		nCount = SSMAX(0, SSMIN(nCount, static_cast<int>(this->size())));
		return this->substr(0, static_cast<MYSIZE>(nCount)); 
	}

#ifndef SS_ANSI
	bool LoadString(UINT nId)
	{
		return this->Load(nId);
	}
#endif

	void MakeLower()
	{
		ToLower();
	}

	void MakeReverse()
	{
		std::reverse(this->begin(), this->end());
	}

	void MakeUpper()
	{ 
		ToUpper();
	}

	MYTYPE Mid(int nFirst) const
	{
		return Mid(nFirst, this->GetLength()-nFirst);
	}

	MYTYPE Mid(int nFirst, int nCount) const
	{

		if ( nFirst < 0 )
			nFirst = 0;
		if ( nCount < 0 )
			nCount = 0;

		int nSize = static_cast<int>(this->size());

		if ( nFirst + nCount > nSize )
			nCount = nSize - nFirst;

		if ( nFirst > nSize )
			return MYTYPE();

		ASSERT(nFirst >= 0);
		ASSERT(nFirst + nCount <= nSize);

		return this->substr(static_cast<MYSIZE>(nFirst),
							static_cast<MYSIZE>(nCount));
	}

	void ReleaseBuffer(int nNewLen=-1)
	{
		RelBuf(nNewLen);
	}

	int Remove(CT ch)
	{
		MYSIZE nIdx		= 0;
		int nRemoved	= 0;
		while ( (nIdx=this->find_first_of(ch)) != MYBASE::npos )
		{
			this->erase(nIdx, 1);
			nRemoved++;
		}
		return nRemoved;
	}

	int Replace(CT chOld, CT chNew)
	{
		int nReplaced	= 0;

		for ( MYITER iter=this->begin(); iter != this->end(); iter++ )
		{
			if ( *iter == chOld )
			{
				*iter = chNew;
				nReplaced++;
			}
		}

		return nReplaced;
	}

	int Replace(PCMYSTR szOld, PCMYSTR szNew)
	{
		int nReplaced		= 0;
		MYSIZE nIdx			= 0;
		MYSIZE nOldLen		= sslen(szOld);

		if ( 0 != nOldLen )
		{

			MYSIZE nNewLen		= sslen(szNew);
			if ( nNewLen > nOldLen )
			{
				int nFound			= 0;
				while ( nIdx < this->length() &&
					(nIdx=this->find(szOld, nIdx)) != MYBASE::npos )
				{
					nFound++;
					nIdx += nOldLen;
				}
				this->reserve(this->size() + nFound * (nNewLen - nOldLen));
			}

			static const CT ch	= CT(0);
			PCMYSTR szRealNew	= szNew == 0 ? &ch : szNew;
			nIdx				= 0;

			while ( nIdx < this->length() && 
				(nIdx=this->find(szOld, nIdx)) != MYBASE::npos )
			{
				this->replace(this->begin()+nIdx, this->begin()+nIdx+nOldLen,
					szRealNew);

				nReplaced++;
				nIdx += nNewLen;
			}
		}

		return nReplaced;
	}

   int ReplaceNoCase(PCMYSTR szOld, PCMYSTR szNew)
   {
      int nReplaced		= 0;
      MYSIZE nIdx			= 0;
      MYSIZE nOldLen		= sslen(szOld);

      if ( 0 != nOldLen )
      {
         MYSIZE nNewLen		= sslen(szNew);
         if ( nNewLen > nOldLen )
         {
            size_t nFound			= 0;
            while ( nIdx < this->length() &&
               (nIdx=this->FindNoCase(szOld, nIdx)) != MYBASE::npos )
            {
               nFound++;
               nIdx += nOldLen;
            }
            this->reserve(this->size() + nFound * (nNewLen - nOldLen));
         }

         static const CT ch	= CT(0);
         PCMYSTR szRealNew	= szNew == 0 ? &ch : szNew;
         nIdx				= 0;

         while ( nIdx < this->length() && 
            (nIdx=this->FindNoCase(szOld, nIdx)) != MYBASE::npos )
         {
            this->replace(this->begin()+nIdx, this->begin()+nIdx+nOldLen,
               szRealNew);

            nReplaced++;
            nIdx += nNewLen;
         }
      }

      return nReplaced;
   }

	int ReverseFind(CT ch) const
	{
		MYSIZE nIdx	= this->find_last_of(ch);
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

	// ReverseFind overload that's not in CString but might be useful
	int ReverseFind(PCMYSTR szFind, MYSIZE pos=MYBASE::npos) const
	{
		MYSIZE nIdx	= this->rfind(0 == szFind ? MYTYPE() : szFind, pos);
		return static_cast<int>(MYBASE::npos == nIdx ? -1 : nIdx);
	}

	MYTYPE Right(int nCount) const
	{
        // Range check the count.

		nCount = SSMAX(0, SSMIN(nCount, static_cast<int>(this->size())));
		return this->substr(this->size()-static_cast<MYSIZE>(nCount));
	}

	void SetAt(int nIndex, CT ch)
	{
		ASSERT(this->size() > static_cast<MYSIZE>(nIndex));
		this->at(static_cast<MYSIZE>(nIndex))		= ch;
	}

	MYTYPE SpanExcluding(PCMYSTR szCharSet) const
	{
        MYSIZE pos = this->find_first_of(szCharSet);
        return pos == MYBASE::npos ? *this : Left(pos);
	}

	MYTYPE SpanIncluding(PCMYSTR szCharSet) const
	{
        MYSIZE pos = this->find_first_not_of(szCharSet);
        return pos == MYBASE::npos ? *this : Left(pos);
	}

	MYTYPE& Trim()
	{
		return TrimLeft().TrimRight();
	}

	MYTYPE& TrimLeft()
	{
		this->erase(this->begin(),
			std::find_if(this->begin(), this->end(), NotSpace<CT>()));

		return *this;
	}

	MYTYPE&  TrimLeft(CT tTrim)
	{
		this->erase(0, this->find_first_not_of(tTrim));
		return *this;
	}

	MYTYPE&  TrimLeft(PCMYSTR szTrimChars)
	{
		this->erase(0, this->find_first_not_of(szTrimChars));
		return *this;
	}

	MYTYPE& TrimRight()
	{
		MYRITER it = std::find_if(this->rbegin(), this->rend(), NotSpace<CT>());
		if ( !(this->rend() == it) )
			this->erase(this->rend() - it);

		this->erase(!(it == this->rend()) ? this->find_last_of(*it) + 1 : 0);
		return *this;
	}

	MYTYPE&  TrimRight(CT tTrim)
	{
		MYSIZE nIdx	= this->find_last_not_of(tTrim);
		this->erase(MYBASE::npos == nIdx ? 0 : ++nIdx);
		return *this;
	}

	MYTYPE&  TrimRight(PCMYSTR szTrimChars)
	{
		MYSIZE nIdx	= this->find_last_not_of(szTrimChars);
		this->erase(MYBASE::npos == nIdx ? 0 : ++nIdx);
		return *this;
	}

	void			FreeExtra()
	{
		MYTYPE mt;
		this->swap(mt);
		if ( !mt.empty() )
			this->assign(mt.c_str(), mt.size());
	}

	CT& operator[](int nIdx)
	{
		return static_cast<MYBASE*>(this)->operator[](static_cast<MYSIZE>(nIdx));
	}

	const CT& operator[](int nIdx) const
	{
		return static_cast<const MYBASE*>(this)->operator[](static_cast<MYSIZE>(nIdx));
	}

	CT& operator[](unsigned int nIdx)
	{
		return static_cast<MYBASE*>(this)->operator[](static_cast<MYSIZE>(nIdx));
	}

	const CT& operator[](unsigned int nIdx) const
	{
		return static_cast<const MYBASE*>(this)->operator[](static_cast<MYSIZE>(nIdx));
	}

#ifndef SS_NO_IMPLICIT_CAST
	operator const CT*() const
	{
		return this->c_str();
	}
#endif

#ifdef SS_INC_COMDEF

	// struct SSSHDR - useful for non Std C++ persistence schemes.
	typedef struct SSSHDR
	{
		BYTE	byCtrl;
		ULONG	nChars;
	} SSSHDR;	// as in "Standard String Stream Header"

	#define SSSO_UNICODE	0x01	// the string is a wide string
	#define SSSO_COMPRESS	0x02	// the string is compressed

	ULONG StreamSize() const
	{
		// Control header plus string
		ASSERT(this->size()*sizeof(CT) < 0xffffffffUL - sizeof(SSSHDR));
		return (this->size() * sizeof(CT)) + sizeof(SSSHDR);
	}

	HRESULT StreamSave(IStream* pStream) const
	{
		ASSERT(this->size()*sizeof(CT) < 0xffffffffUL - sizeof(SSSHDR));
		HRESULT hr		= E_FAIL;
		ASSERT(pStream != 0);
		SSSHDR hdr;
		hdr.byCtrl		= sizeof(CT) == 2 ? SSSO_UNICODE : 0;
		hdr.nChars		= this->size();


		if ( FAILED(hr=pStream->Write(&hdr, sizeof(SSSHDR), 0)) )
		{
			TRACE(PLATFORM_STRING("StreamSave: Cannot write control header, ERR=0x%X\n"),hr);
		}
		else if ( empty() )
		{
			;		// nothing to write
		}
		else if ( FAILED(hr=pStream->Write(this->c_str(),
			this->size()*sizeof(CT), 0)) )
		{
			TRACE(PLATFORM_STRING("StreamSave: Cannot write string to stream 0x%X\n"), hr);
		}

		return hr;
	}

	HRESULT StreamLoad(IStream* pStream)
	{
		ASSERT(pStream != 0);
		SSSHDR hdr;
		HRESULT hr			= E_FAIL;

		if ( FAILED(hr=pStream->Read(&hdr, sizeof(SSSHDR), 0)) )
		{
			TRACE(PLATFORM_STRING("StreamLoad: Cant read control header, ERR=0x%X\n"), hr);
		}
		else if ( hdr.nChars > 0 )
		{
			ULONG nRead		= 0;
			PMYSTR pMyBuf	= BufferSet(hdr.nChars);
			
			if ( (hdr.byCtrl & SSSO_UNICODE) != 0 )
			{
				ULONG nBytes	= hdr.nChars * sizeof(wchar_t);
				if ( sizeof(CT) == sizeof(wchar_t) )
				{
					if ( FAILED(hr=pStream->Read(pMyBuf, nBytes, &nRead)) )
						TRACE(PLATFORM_STRING("StreamLoad: Cannot read string: 0x%X\n"), hr);
				}
				else
				{	
					PWSTR pBufW = reinterpret_cast<PWSTR>(_alloca((nBytes)+1));
					if ( FAILED(hr=pStream->Read(pBufW, nBytes, &nRead)) )
						TRACE(PLATFORM_STRING("StreamLoad: Cannot read string: 0x%X\n"), hr);
					else
						sscpy(pMyBuf, pBufW, hdr.nChars);
				}
			}
			else
			{
				ULONG nBytes	= hdr.nChars * sizeof(char);
				if ( sizeof(CT) == sizeof(char) )
				{
					if ( FAILED(hr=pStream->Read(pMyBuf, nBytes, &nRead)) )
						TRACE(PLATFORM_STRING("StreamLoad: Cannot read string: 0x%X\n"), hr);
				}
				else
				{
					PSTR pBufA = reinterpret_cast<PSTR>(_alloca(nBytes));
					if ( FAILED(hr=pStream->Read(pBufA, hdr.nChars, &nRead)) )
						TRACE(PLATFORM_STRING("StreamLoad: Cannot read string: 0x%X\n"), hr);
					else
						sscpy(pMyBuf, pBufA, hdr.nChars);
				}
			}
		}
		else
		{
			this->erase();
		}
		return hr;
	}
#endif // #ifdef SS_INC_COMDEF

};
typedef CStdStr<char>		CStdStringA;	// a better std::string
typedef CStdStr<wchar_t>	CStdStringW;	// a better std::wstring
typedef CStdStr<OLECHAR>	CStdStringO;	// almost always CStdStringW

inline CStdStringA operator+(const CStdStringA& s1, const CStdStringA& s2)
{
	CStdStringA sRet(SSREF(s1));
	sRet.append(s2);
	return sRet;
}
inline CStdStringA operator+(const CStdStringA& s1, CStdStringA::value_type t)
{
	CStdStringA sRet(SSREF(s1));
	sRet.append(1, t);
	return sRet;
}
inline CStdStringA operator+(const CStdStringA& s1, PCSTR pA)
{
	CStdStringA sRet(SSREF(s1));
	sRet.append(pA);
	return sRet;
}
inline CStdStringA operator+(PCSTR pA, const CStdStringA& sA)
{
	CStdStringA sRet;
	CStdStringA::size_type nObjSize = sA.size();
	CStdStringA::size_type nLitSize = 
		static_cast<CStdStringA::size_type>(sslen(pA));

	sRet.reserve(nLitSize + nObjSize);
	sRet.assign(pA);
	sRet.append(sA);
	return sRet;
}


inline CStdStringA operator+(const CStdStringA& s1, const CStdStringW& s2)
{
	return s1 + CStdStringA(s2);
}
inline CStdStringW operator+(const CStdStringW& s1, const CStdStringW& s2)
{
	CStdStringW sRet(SSREF(s1));
	sRet.append(s2);
	return sRet;
}
inline CStdStringA operator+(const CStdStringA& s1, PCWSTR pW)
{
	return s1 + CStdStringA(pW);
}

	inline CStdStringW operator+(PCWSTR pW, const CStdStringA& sA)
	{
		return CStdStringW(pW) + CStdStringW(SSREF(sA));
	}
	inline CStdStringW operator+(PCSTR pA, const CStdStringW& sW)
	{
		return CStdStringW(pA) + sW;
	}

// ...Now the wide string versions.
inline CStdStringW operator+(const CStdStringW& s1, CStdStringW::value_type t)
{
	CStdStringW sRet(SSREF(s1));
	sRet.append(1, t);
	return sRet;
}
inline CStdStringW operator+(const CStdStringW& s1, PCWSTR pW)
{
	CStdStringW sRet(SSREF(s1));
	sRet.append(pW);
	return sRet;
}
inline CStdStringW operator+(PCWSTR pW, const CStdStringW& sW)
{
	CStdStringW sRet;
	CStdStringW::size_type nObjSize = sW.size();
	CStdStringA::size_type nLitSize = 
		static_cast<CStdStringW::size_type>(sslen(pW));

	sRet.reserve(nLitSize + nObjSize);
	sRet.assign(pW);
	sRet.append(sW);
	return sRet;
}

inline CStdStringW operator+(const CStdStringW& s1, const CStdStringA& s2)
{
	return s1 + CStdStringW(s2);
}
inline CStdStringW operator+(const CStdStringW& s1, PCSTR pA)
{
	return s1 + CStdStringW(pA);
}

#ifdef SS_SAFE_FORMAT

template<>
struct FmtArg<CStdStringA>
{
    explicit FmtArg(const CStdStringA& arg) : a_(arg) {}
    PCSTR operator()() const { return a_.c_str(); }
    const CStdStringA& a_;
private:
    FmtArg<CStdStringA>& operator=(const FmtArg<CStdStringA>&) { return *this; }
};
template<>
struct FmtArg<CStdStringW>
{
    explicit FmtArg(const CStdStringW& arg) : a_(arg) {}
    PCWSTR operator()() const { return a_.c_str(); }
    const CStdStringW& a_;
private:
    FmtArg<CStdStringW>& operator=(const FmtArg<CStdStringW>&) { return *this; }
};

template<>
struct FmtArg<std::string>
{
    explicit FmtArg(const std::string& arg) : a_(arg) {}
    PCSTR operator()() const { return a_.c_str(); }
    const std::string& a_;
private:
    FmtArg<std::string>& operator=(const FmtArg<std::string>&) { return *this; }
};
template<>
struct FmtArg<std::wstring>
{
    explicit FmtArg(const std::wstring& arg) : a_(arg) {}
    PCWSTR operator()() const { return a_.c_str(); }
    const std::wstring& a_;
private:
    FmtArg<std::wstring>& operator=(const FmtArg<std::wstring>&) {return *this;}
};
#endif // #ifdef SS_SAFEFORMAT

inline CStdStringA WUFormatA(PCSTR szFormat, ...)
{
	va_list argList;
	va_start(argList, szFormat);
	CStdStringA strOut;
	strOut.FormatV(szFormat, argList);
	va_end(argList);
	return strOut;
}
inline CStdStringW WUFormatW(PCWSTR szwFormat, ...)
{
	va_list argList;
	va_start(argList, szwFormat);
	CStdStringW strOut;
	strOut.FormatV(szwFormat, argList);
	va_end(argList);
	return strOut;
}
// Define TCHAR based friendly names for some of these functions

typedef CStdStringW				CStdString;
#define WUSysMessage			WUSysMessageW
#define WUFormat				WUFormatW

// ...and some shorter names for the space-efficient

#define WUSysMsg					WUSysMessage
#define WUSysMsgA					WUSysMessageA
#define WUSysMsgW					WUSysMessageW
#define WUFmtA						WUFormatA
#define	WUFmtW						WUFormatW
#define WUFmt						WUFormat
#define WULastErrMsg()				WUSysMessage(::GetLastError())
#define WULastErrMsgA()				WUSysMessageA(::GetLastError())
#define WULastErrMsgW()				WUSysMessageW(::GetLastError())

#define StdStringLessNoCaseW		SSLNCW	// avoid VC compiler warning 4786
#define StdStringEqualsNoCaseW		SSENCW		
#define StdStringLessNoCaseA		SSLNCA		
#define StdStringEqualsNoCaseA		SSENCA		

#ifdef UNICODE
	#define StdStringLessNoCase		SSLNCW		
	#define StdStringEqualsNoCase	SSENCW		
#else
	#define StdStringLessNoCase		SSLNCA		
	#define StdStringEqualsNoCase	SSENCA		
#endif

struct StdStringLessNoCaseW
	: std::binary_function<CStdStringW, CStdStringW, bool>
{
	inline
	bool operator()(const CStdStringW& sLeft, const CStdStringW& sRight) const
	{ return ssicmp(sLeft.c_str(), sRight.c_str()) < 0; }
};
struct StdStringEqualsNoCaseW
	: std::binary_function<CStdStringW, CStdStringW, bool>
{
	inline
	bool operator()(const CStdStringW& sLeft, const CStdStringW& sRight) const
	{ return ssicmp(sLeft.c_str(), sRight.c_str()) == 0; }
};
struct StdStringLessNoCaseA
	: std::binary_function<CStdStringA, CStdStringA, bool>
{
	inline
	bool operator()(const CStdStringA& sLeft, const CStdStringA& sRight) const
	{ return ssicmp(sLeft.c_str(), sRight.c_str()) < 0; }
};
struct StdStringEqualsNoCaseA
	: std::binary_function<CStdStringA, CStdStringA, bool>
{
	inline
	bool operator()(const CStdStringA& sLeft, const CStdStringA& sRight) const
	{ return ssicmp(sLeft.c_str(), sRight.c_str()) == 0; }
};

// If we had to define our own version of TRACE above, get rid of it now

#ifdef TRACE_DEFINED_HERE
	#undef TRACE
	#undef TRACE_DEFINED_HERE
#endif


#endif	// #ifndef STDSTRING_H

namespace HM 
{ 
   typedef CStdStr<wchar_t> String; 
   typedef CStdStr<char> AnsiString; 
}
