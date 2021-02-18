#ifndef COCOATWEET_API_FAVORITE_DESTROY_H_
#define COCOATWEET_API_FAVORITE_DESTROY_H_

#include <cocoatweet/api/interface/postInterface.h>

namespace CocoaTweet::API::Favorites {
class Destroy : public CocoaTweet::API::Interface::postInterface {
public:
  Destroy();
  void id(const std::string& _id);

private:
};
} // namespace CocoaTweet::API::Favorites

#endif