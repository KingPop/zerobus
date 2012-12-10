// Copyright (c) 2012,  Reve Zhang.
// All rights reserved.
//
// Author: Reve Zhang <weiffun@gmail.com>
// Created: 2012/11/24
// Version: 1.0

#ifndef zerobus_DEALER2DEALERPATTERN_H__
#define zerobus_DEALER2DEALERPATTERN_H__

#include "../zmqbind/zmqbind.hpp"
#include "IPeer.hpp"

namespace zerobus {
	namespace framework {

		//�����ˣ���������������
		class DealerActivePeer : public ActivePeer
		{
		public:
			DealerActivePeer();

			~DealerActivePeer();

			int Init(zmqbind::Context& ctx);

			//ͬ����������, ����sync�����Զ�
			//�ȴ�time_out���������ݰ�����-2��-1�����ʾ���޵ȴ�
			int Connect(const char* endpoint, int time_out, const char* dealer_name);

			//�첽��������
			int Send(const void* pmsg, int len);

			//���͵�ָ��peer
			int SendToPeer(IPeer* peer, const void* pmsg, int len);

			//�첽��������
			int Recv(void* pmsg, int& len);

			//��ȡԭʼ�׽���
			void* GetRawSocket() { return _socket.GetRawSocket(); };

			int KeepAlive();

		private:
			int SendConnectMsg();

		private:
			zmqbind::Socket _socket;
		};

		//�����ˣ�����ָ���˿�
		class DealerPassivePeer : public PassivePeer
		{
		public:
			DealerPassivePeer();

			~DealerPassivePeer();

			int Init(zmqbind::Context& ctx);

			//�󶨵�ָ���˿�
			int Bind(const char* endpoint);

			//��������
			int Send(const void* pmsg, int len);

			//���͵�ָ��peer
			int SendToPeer(IPeer* peer, const void* pmsg, int len);

			//��������
			int Recv(void* pmsg, int& len);

			//��ȡԭʼ�׽���
			void* GetRawSocket() { return _socket.GetRawSocket(); };

			int KeepAlive();

		private:
			zmqbind::Socket _socket;
		};
	}
}

#endif // zerobus_DEALER2DEALERPATTERN_H__
