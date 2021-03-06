#pragma once
#include "StockComEvent.h"

// 普通行情事件处理辅助类
class CMarketEvent : 
	public CComObjectRoot,
	//实现普通行情事件通知接口
	public _IMarketEvents
{
protected:

	/// 连接对象序号
	USHORT			m_nConnIndex;
	/// 请求ID
	ULONG			m_nRequestID;
	/// 父窗口
	HWND			m_hParentWnd;

	/// 返回数据缓存
	ITradeRecordPtr	m_spiRecord;

	/// 普通行情接口
	IMarketPtr		m_spiMarket;

	/// 错误描述
	CString			m_strErrInfo;

public:
	CMarketEvent()
		:m_hParentWnd(NULL)
		,m_spiRecord(NULL)
		,m_spiMarket(NULL)
		,m_nConnIndex(0)
		,m_nRequestID(0)
	{
	}

	~CMarketEvent()
	{
		m_spiRecord = NULL;
	}

	void SetCallPara(HWND hParentWnd,USHORT nIndex)
	{
		if(NULL != hParentWnd)
		{
			if(!::IsWindow(hParentWnd))
				return;
		}
		m_nConnIndex = nIndex;
		m_hParentWnd = hParentWnd;
	}

	ITradeRecordPtr GetReqData()
	{
		return m_spiRecord;
	}

	ULONG GetReqID()
	{
		return m_nRequestID;
	}

	IMarketPtr GetMarket()
	{
		return m_spiMarket;
	}

BEGIN_COM_MAP(CMarketEvent)
	COM_INTERFACE_ENTRY(_IMarketEvents)
END_COM_MAP()

public:

	STDMETHODIMP GetTypeInfoCount(UINT*)
    {
       return E_NOTIMPL;
    }

    STDMETHODIMP GetTypeInfo( UINT iTInfo,LCID lcid,ITypeInfo **ppTInfo)
    { 
       return E_NOTIMPL;
    }

    STDMETHODIMP GetIDsOfNames( REFIID riid,LPOLESTR *rgszNames,UINT cNames,
                    LCID lcid,DISPID *rgDispId)
    { 
      return E_NOTIMPL;
    }

	STDMETHOD(Invoke)(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS *pDispParams,
               VARIANT *pVarResult,EXCEPINFO *pExcepInfo,UINT *puArgErr);
	
	//  _IMarketEvents
	/// 初始化接口结果通知
	STDMETHOD(InitEvent)(IDispatch* piMarket,VARIANT_BOOL bOK);
	/// 连接服务器结果通知
	STDMETHOD(ConnectEvent)(IDispatch* piMarket, ULONG nConnID,BSTR bstrHost,USHORT nPort,VARIANT_BOOL bOK);
	/// 查询指定股票实时5档行情回报
	STDMETHOD(StockQuoteEvent)(ULONG nReqID,IDispatch* piRecordInfo);
	/// 查询指定股票分时行情回报
	STDMETHOD(StockMinuteEvent)(ULONG nReqID,BSTR bstrCode,IDispatch* piRecordInfo);
	/// 查询指定股票分时成交回报
	STDMETHOD(StockTransEvent)(ULONG nReqID,BSTR bstrCode,IDispatch* piRecordInfo);
	/// 查询指定股票K线回报
	STDMETHOD(StockBarsEvent)(ULONG nReqID,BSTR bstrCode,IDispatch* piRecordInfo);

	/// 服务器错误通知
	STDMETHOD(ServerErrEvent)(ULONG nConnID,ULONG nReqID);
};