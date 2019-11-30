/*

Copyright (c) 2003-2004, 2006-2007, 2009-2010, 2013-2019, Arvid Norberg
Copyright (c) 2015, Steven Siloti
Copyright (c) 2016-2018, Alden Torres
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TORRENT_SESSION_PARAMS_HPP_INCLUDED
#define TORRENT_SESSION_PARAMS_HPP_INCLUDED

#include <functional>
#include <memory>
#include <vector>

#include "libtorrent/config.hpp"
#include "libtorrent/aux_/export.hpp"
#include "libtorrent/settings_pack.hpp"
#include "libtorrent/io_context.hpp"
#include "libtorrent/kademlia/dht_state.hpp"
#include "libtorrent/session_types.hpp"
#include "libtorrent/kademlia/dht_storage.hpp"

#if TORRENT_ABI_VERSION <= 2
#include "libtorrent/kademlia/dht_settings.hpp"
#endif

namespace libtorrent {

struct plugin;
struct disk_interface;
struct counters;

using disk_io_constructor_type = std::function<std::unique_ptr<disk_interface>(
	io_context&, settings_interface const&, counters&)>;

TORRENT_VERSION_NAMESPACE_3

// The session_params is a parameters pack for configuring the session
// before it's started.
struct TORRENT_EXPORT session_params
{
	// This constructor can be used to start with the default plugins
	// (ut_metadata, ut_pex and smart_ban). The default values in the
	// settings is to start the default features like upnp, NAT-PMP,
	// and dht for example.
	session_params(settings_pack&& sp); // NOLINT
	session_params(settings_pack const& sp); // NOLINT
	session_params();
	~session_params();

	// This constructor helps to configure the set of initial plugins
	// to be added to the session before it's started.
	session_params(settings_pack&& sp
		, std::vector<std::shared_ptr<plugin>> exts);
	session_params(settings_pack const& sp
		, std::vector<std::shared_ptr<plugin>> exts);

	// hidden
	session_params(session_params const&);
	session_params(session_params&&);
	session_params& operator=(session_params const&) &;
	session_params& operator=(session_params&&) &;

	settings_pack settings;

	std::vector<std::shared_ptr<plugin>> extensions;

#if TORRENT_ABI_VERSION <= 2
#ifdef _MSC_VER
#pragma warning(push, 1)
#pragma warning( disable : 4996 ) // warning C4996: X: was declared deprecated
#endif
#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
	// this is deprecated. Use the dht_* settings instead.
	dht::dht_settings dht_settings;
#if defined __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

	dht::dht_state dht_state;

	dht::dht_storage_constructor_type dht_storage_constructor;

	disk_io_constructor_type disk_io_constructor;
};

TORRENT_VERSION_NAMESPACE_3_END

}

#endif
