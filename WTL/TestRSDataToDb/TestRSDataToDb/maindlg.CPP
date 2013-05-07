#include "StdAfx.h"
#include "MainDlg.h"
#include "PathUtil.h"

LRESULT CMainDlg::OnBnClickedButtonSelectSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	RG::CPathUtil clsPathUtil;
	clsPathUtil.GetSelectDirDlg(this->m_hWnd, IDC_EDIT_SOURCE_PATH, _T("ѡ��·��2"));
	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonSelectLink(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	RG::CPathUtil clsPathUtil;
	clsPathUtil.GetSelectDirDlg(this->m_hWnd, IDC_EDIT_LINK_PATH);
	//clsPathUtil.GetFileDlg(this->m_hWnd, IDC_EDIT_LINK_PATH, false, _T("��ҳ�ļ�(*.html)\0*.html\0;��ҳ�ļ�(*.htm)\0*.htm\0;All Files(*.*)\0*.*\0"));
	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonStart(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl */, BOOL& /*bHandled*/)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	int iInterval = GetDlgItemInt(IDC_EDIT_INTERVAL);
	TCHAR tszLinkPath[MAX_PATH] = {0};
	TCHAR tszSourcePath[MAX_PATH] = {0};
	GetDlgItemText(IDC_EDIT_LINK_PATH, tszLinkPath, MAX_PATH);
	GetDlgItemText(IDC_EDIT_SOURCE_PATH, tszSourcePath, MAX_PATH);
	
	if (!(_tcslen(tszSourcePath) && _tcslen(tszLinkPath)))
	{
		::MessageBox(NULL, _T("�������ѡ��Source��Link·��!!!"), _T("TIP_RG"), MB_OK);
		return 0;
	}

	m_pclsHandleFile = new CHandleFile;
	m_pclsHandleFile->Start(tszSourcePath, tszLinkPath, iInterval);
	

	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������

	m_pclsHandleFile->Stop();
	Sleep(1000);
	delete m_pclsHandleFile;
	::MessageBox(NULL, _T("�Ѿ�ֹͣ��������"), _T("Stop"), MB_OK);
	return 0;
}