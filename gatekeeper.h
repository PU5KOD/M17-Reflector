//
//  cgatekeeper.h
//  M17Refd
//
//  Created by Jean-Luc Deltombe (LX3JL) on 07/11/2015.
//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
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

#include "main.h"
#include "callsign.h"
#include "ip.h"
#include "bwset.h"
#include "peermap.h"

////////////////////////////////////////////////////////////////////////////////////////
// class

class CGateKeeper
{
public:
	// constructor
	CGateKeeper();

	// destructor
	~CGateKeeper();

	// init & clode
	bool Init(void);
	void Close(void);

	// authorizations
	bool MayLink(const CCallsign &, const CIp &, char * = nullptr) const;
	bool MayTransmit(const CCallsign &, const CIp &) const;

	// peer list handeling
	CPeerMap *GetPeerMap(void)     { m_PeerMap.Lock(); return &m_PeerMap; }
	void      ReleasePeerMap(void) { m_PeerMap.Unlock(); }

protected:
	// thread
	void Thread();

	// operation helpers
	bool IsNodeListedOk(const CCallsign &) const;
	bool IsPeerListedOk(const CCallsign &, const CIp &, const char *) const;

protected:
	// data
	CBWSet   m_NodeWhiteSet;
	CBWSet   m_NodeBlackSet;
	CPeerMap m_PeerMap;

	// thread
	std::atomic<bool> keep_running;
	std::future<void> m_Future;
};
