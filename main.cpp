#include <base/net/ethernet/EthernetFrameReader.h>
#include <base/string/ToHexString.h>
#include <format>
#include <iostream>
#include <pcappp/Pcap.h>

int main()
{
    std::cout << pcappp::Pcap::Version() << std::endl;
    std::shared_ptr<base::IEnumerable<std::shared_ptr<pcappp::IPcapInterface>>> interface_list = pcappp::Pcap::FindInterfaces();
    // std::shared_ptr<pcappp::IPcapInterface> pcap_interface = pcappp::Pcap::FindInterfaceByDescription("Network adapter 'Realtek PCIe GbE Family Controller' on local host");
    // std::shared_ptr<pcappp::IPcapInterface> pcap_interface = pcappp::Pcap::FindInterfaceByDescription("Network adapter 'Intel(R) Wi-Fi 6 AX200 160MHz' on local host");
    std::shared_ptr<pcappp::IPcapInterface> pcap_interface = pcappp::Pcap::FindInterfaceByDescription("Network adapter 'Intel(R) Ethernet Controller (3) I225-V' on local host");
    if (pcap_interface != nullptr)
    {
        pcap_interface->Open();
        pcap_interface->CaptureOnePacket();
        if (pcap_interface->CaptureResult().Code() == pcappp::CaptureResultCode::Success)
        {
            std::cout << "success" << std::endl;
        }

        std::cout << pcap_interface->LinkType() << std::endl;
        std::cout << pcap_interface->CaptureResult().Timestamp() << std::endl;
        std::cout << pcap_interface->CaptureResult().CaptureLength() << std::endl;

        base::ethernet::EthernetFrameReader frame{pcap_interface->CaptureResult().Buffer()};
        std::cout << frame << std::endl;
    }

    return 0;
}
