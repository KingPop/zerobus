// Copyright (c) 2012,  Reve Zhang.
// All rights reserved.
//
// Author: Reve Zhang <weiffun@gmail.com>
// Created: 2012/11/24
// Version: 1.0

#ifndef NETBUS_IPEER_H__
#define NETBUS_IPEER_H__

#define NOTCOPYBLE(TYPE) \
		TYPE(const TYPE&);\
		void operator=(const TYPE&);\

namespace netbus {
	namespace framework {

		enum PRSERVED_MSG {
			PRSERVED_MSG_CONN = 1,
			PRSERVED_MSG_CONN_RSP = 2,
			PRSERVED_MSG_HEARTBEAT = 3
		};

		void FreeCallback(void *, void *);
	

		//����˳���ӿ�
		class IPeer {
		public:
			IPeer() {};
			virtual ~IPeer() {};

			virtual int Init(zmqbind::Context& ctx) = 0;

			//��������
			virtual int Send(const void* pmsg, int len) = 0;

			//���͵�ָ��peer
			virtual int SendToPeer(IPeer* peer, const void* pmsg, int len) = 0;

			//��������
			virtual int Recv(void* pmsg, int& len) = 0;

			//��ȡԭʼ�׽���
			virtual void* GetRawSocket() = 0;

			virtual int KeepAlive() = 0;

		private:
			NOTCOPYBLE(IPeer)
		};

		//�����ˣ���������������
		class ActivePeer : public IPeer
		{
		public:
			ActivePeer() {};

			virtual ~ActivePeer() {};

			//ͬ����������, ����sync�����Զ�
			//�ȴ�time_out���������ݰ�����-2��-1�����ʾ���޵ȴ�
			virtual int Connect(const char* endpoint, int time_out, const char* dealer_name) = 0;
		};

		//�����ˣ�����ָ���˿�
		class PassivePeer : public IPeer
		{
		public:
			PassivePeer() {};

			virtual ~PassivePeer() {};

			virtual int Bind(const char* endpoint) = 0;
		};
	}
}

#endif // NETBUS_IPEER_H__
