#include "UdpConversation.h"

namespace FeatureExtractor {

	UdpConversation::UdpConversation()
	{
	}

	UdpConversation::UdpConversation(const FiveTuple *tuple)
		: Conversation(tuple)
	{
	}

	UdpConversation::UdpConversation(const Packet *packet)
		: Conversation(packet)
	{
	}


	UdpConversation::~UdpConversation()
	{
	}


	service_t UdpConversation::get_service() const
	{
		switch (five_tuple.get_dst_port())
		{
		case 53:	// DNS
			return SRV_DOMAIN_U;
			break;

		case 69:	// TFTP
			return SRV_TFTP_U;
			break;

		case 123:	// NTP
			return SRV_NTP_U;
			break;

		case 5355: // Link-Local Multicast Name Resolution (LLMNR)
			return SRV_LLMNR_U;
			break;

		case 1900: // Simple Service Discovery Protocol (SSDP)
			return SRV_SSDP_U;
			break;

		case 67: // Dynamic Host Configuration Protocol (DHCP) - DHCPDISCOVER or DHCPREQUEST
		case 68: // Dynamic Host Configuration Protocol (DHCP) - DHCPOFFER or DHCPACK
			return SRV_DHCP_U;
			break;

		case 138: // NETBIOS Datagram Service
			return SRV_NETBIOS_DGM_U;
			break;

		case 137: // NETBIOS Name Service
			return SRV_NETBIOS_NS_U;
			break;

		case 3702: // Web Services Dynamic Discovery (WS-Discovery)
			return SRV_WS_DISCOVERY_U;
			break;

		default:
			// Defined by IANA in RFC 6335 section 6:
			// the Dynamic Ports, also known as the Private or Ephemeral Ports,
			// from 49152 - 65535 (never assigned)
			if (five_tuple.get_dst_port() >= 49152)
				return SRV_PRIVATE;
			else
				return SRV_OTHER;
			break;
		}

		return SRV_OTHER;
	}
}
