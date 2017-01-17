#include <mutex>
#include <shared_mutex>
#include "QApplicationWatcher.hpp"

namespace qappwatcher {
extern std::shared_timed_mutex * getMutex();
}

namespace qappwatcher {

namespace {
using mutex_data_t=std::aligned_storage_t<
    sizeof(std::shared_timed_mutex),alignof(std::shared_timed_mutex)>;
mutex_data_t mutex_data;
}/*namespace*/

std::shared_timed_mutex * getMutex() {
    static auto ans=::new(&mutex_data) std::shared_timed_mutex;
    return ans;
}

}

