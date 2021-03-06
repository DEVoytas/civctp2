#if defined(HAVE_PRAGMA_ONCE)
#pragma once
#endif

#ifndef __C3_BUTTON_H__
#define __C3_BUTTON_H__

class c3_Button;
class c3_EditButton;

#define k_C3_BUTTON_DEFAULT_BEVELWIDTH		2
#define k_C3_BUTTON_LDL_BEVELWIDTH			"bevelwidth"
#define k_C3_BUTTON_LDL_BEVELTYPE			"beveltype"

#define k_C3_EDITBUTTON_LDL_FIELD			"field"
#define k_C3_EDITBUTTON_LDL_VAL				"val"
#define k_C3_EDITBUTTON_LDL_MINVAL			"min"
#define k_C3_EDITBUTTON_LDL_MAXVAL			"max"
#define k_C3_EDITBUTTON_DEFAULTVAL			0
#define k_C3_EDITBUTTON_DEFAULTMIN			0
#define k_C3_EDITBUTTON_DEFAULTMAX			100

#include "patternbase.h"
#include "aui_action.h"
#include "aui_button.h"

class aui_Surface;
class C3TextField;

class c3_Button : public aui_Button, public PatternBase
{
public:
	c3_Button(
		AUI_ERRCODE *retval,
		uint32 id,
		const MBCHAR *ldlBlock,
		ControlActionCallback *ActionFunc = NULL,
		void *cookie = NULL );
	c3_Button(
		AUI_ERRCODE *retval,
		uint32 id,
		sint32 x,
		sint32 y,
		sint32 width,
		sint32 height,
		const MBCHAR *pattern,
		ControlActionCallback *ActionFunc = NULL,
		void *cookie = NULL );
	virtual ~c3_Button() {}

	void SetBevelWidth(uint32 w) { m_bevelWidth = w; };

	virtual AUI_ERRCODE DrawThis(
		aui_Surface *surface = NULL,
		sint32 x = 0,
		sint32 y = 0 );

protected:
	c3_Button()
    :
        aui_Button      (),
        PatternBase     (),
        m_bevelWidth    (k_C3_BUTTON_DEFAULT_BEVELWIDTH),
        m_bevelType     (0)
    {};

	AUI_ERRCODE InitCommonLdl( const MBCHAR *ldlBlock );

private:
	uint32	m_bevelWidth;
	uint32	m_bevelType;
};


class c3_EditButton : public c3_Button
{
public:
	c3_EditButton(
		AUI_ERRCODE *retval,
		uint32 id,
		const MBCHAR *ldlBlock,
		ControlActionCallback *ActionFunc = NULL,
		void *cookie = NULL );
	c3_EditButton(
		AUI_ERRCODE *retval,
		uint32 id,
		sint32 x,
		sint32 y,
		sint32 width,
		sint32 height,
		const MBCHAR *pattern,
		ControlActionCallback *ActionFunc = NULL,
		void *cookie = NULL );
	virtual ~c3_EditButton();

	sint32		GetValue( void ) const { return m_val; }
	sint32		GetMinimum( void ) const { return m_min; }
	sint32		GetMaximum( void ) const { return m_max; }

	AUI_ERRCODE	SetValue( sint32 val );
	AUI_ERRCODE	SetMinimum( sint32 min );
	AUI_ERRCODE	SetMaximum( sint32 max );

	void DoCallback( void );

protected:
	c3_EditButton()
    :
        c3_Button       (),
	    m_val           (k_C3_EDITBUTTON_DEFAULTVAL),
	    m_min           (k_C3_EDITBUTTON_DEFAULTMIN),
	    m_max           (k_C3_EDITBUTTON_DEFAULTMAX),
        m_field         (NULL),
        m_origAction    (NULL),
	    m_origCallback  (NULL)
    {};

	AUI_ERRCODE InitCommonLdl( const MBCHAR *ldlBlock );

private:
	sint32 m_val;
	sint32 m_min;
	sint32 m_max;

	C3TextField *m_field;

	union
	{
		aui_Action *m_origAction;
		void *m_origCookie;
	};
	ControlActionCallback * m_origCallback;

	AUI_ERRCODE CreateFieldAndActions( const MBCHAR *ldlBlock = NULL );
};

void c3_EditButtonCallback( aui_Control *, uint32, uint32, void * );
void c3_EditButtonFieldCallback( aui_Control *, uint32, uint32, void * );

#endif
