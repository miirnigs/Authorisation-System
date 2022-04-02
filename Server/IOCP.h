#pragma once
#include <Windows.h>

// ��ɶ˿ڵķ�װ�࣬ȫ����������Դ�ļ�����һ��
class CIOCP
{
public:
	CIOCP() :m_hIOCP(NULL) {}		// Ĭ�Ϲ��캯��
	~CIOCP()		// ��������
	{
		// ɾ�����
		if (m_hIOCP != NULL)
		{
			CloseHandle(m_hIOCP);
		}
	}
public:
	// ������ɶ˿�
	bool Create()
	{
		// ������ɶ˿�
		// FileHandle: �򿪵��ļ��������Ϊ�����Ǵ�����ɶ˿ڣ���������ΪINVALID_HANDLE_VALUE
		// ExistingCompletionPort: ���е�I/O�˿ھ������Ϊ�����Ǵ�����ɶ˿ڣ�������NULL
		// CompletionKey: �����Կ
		// NumberOfConcurrentThreads: ����߳�����0=��ǰCPU������
		m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		return (m_hIOCP != NULL);
	}

	// ��Socket�󶨵���ɶ˿���
	bool AssociateSocket(SOCKET hSocket, ULONG_PTR CompKey)
	{
		return (CreateIoCompletionPort((HANDLE)hSocket, m_hIOCP, CompKey, 0) == m_hIOCP);
	}

	// ������ɶ˿ھ������
	const HANDLE GetIOCP()
	{
		return m_hIOCP;
	}

	// ����ɶ˿ڷ���ָ��״̬
	bool PostStatus(ULONG_PTR CompKey, DWORD dwNumBytes = 0, OVERLAPPED* po = NULL)
	{
		return PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, CompKey, po);
	}
private:
	HANDLE m_hIOCP;		// ��ɶ˿ڵľ��
};
