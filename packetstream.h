//
//  Created by Jean-Luc Deltombe (LX3JL) on 06/11/2015.
//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
//  Copyright © 2020 Thomas A. Early N7TAE
//
// ----------------------------------------------------------------------------
//    This file is part of M17Refd.
//
//    M17Refd is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    M17Refd is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    with this software.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#pragma once

#include "packetqueue.h"
#include "timepoint.h"
#include "packet.h"

////////////////////////////////////////////////////////////////////////////////////////

//#define STREAM_TIMEOUT      (0.600)
#define STREAM_TIMEOUT      (1.600)

////////////////////////////////////////////////////////////////////////////////////////
// class

class CPacketStream : public CPacketQueue
{
public:
	// constructor
	CPacketStream();

	// open / close
	bool OpenPacketStream(const CPacket &, std::shared_ptr<CClient>);
	void ClosePacketStream(void);

	// push & pop
	void Push(std::unique_ptr<CPacket> packet);
	void Tickle(void)                               { m_LastPacketTime.Now(); }
	bool IsEmpty(void) const;

	// get
	std::shared_ptr<CClient> GetOwnerClient(void)   { return m_OwnerClient; }
	const CIp       *GetOwnerIp(void);
	bool             IsExpired(void) const          { return (m_LastPacketTime.DurationSinceNow() > STREAM_TIMEOUT); }
	bool             IsOpen(void) const             { return m_bOpen; }
	uint16_t         GetPacketStreamId(void) const  { return m_uiStreamId; }
	const CCallsign &GetUserCallsign(void) const    { return m_Header.GetDestCallsign(); }

protected:
	// data
	bool                     m_bOpen;
	uint16_t                 m_uiStreamId;
	CTimePoint               m_LastPacketTime;
	CPacket                  m_Header;
	std::shared_ptr<CClient> m_OwnerClient;
};
