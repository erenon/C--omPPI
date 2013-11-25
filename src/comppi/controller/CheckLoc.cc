#include <stdexcept>

#include <comppi/controller/CheckLoc.h>

#include <comppi/service/localization/Localization.h>
#include <comppi/service/log/Log.h>

namespace comppi {
namespace controller {

CheckLoc::CheckLoc(service::Container& container)
    :_container(container)
{}

int CheckLoc::check() {
    try {
        service::localization::Localization::ServiceFactory::create(_container);
    } catch (const std::exception& ex) {
        ERROR << ex.what();
        return 1;
    }

    return 0;
}

} // namespace controller
} // namespace comppi
