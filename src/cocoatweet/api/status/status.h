#ifndef COCOATWEET_API_STATUS_STATUS_H_
#define COCOATWEET_API_STATUS_STATUS_H_

#include "cocoatweet/api/interface/groupInterface.h"
#include "cocoatweet/oauth/oauth.h"
#include <cocoatweet/api/model/tweet.h>
#include <vector>

namespace CocoaTweet::API::Statuses {
class Status : public groupInterface {
public:
  Status() = default;
  Status(std::shared_ptr<CocoaTweet::OAuth::OAuth1> _oauth);
  CocoaTweet::API::Model::Tweet Update(const std::string& _status) const;

  CocoaTweet::API::Model::Tweet Update(const std::string& _status,
                                       std::vector<std::string> _mediaId) const;

  CocoaTweet::API::Model::Tweet Destroy(const std::string& _id) const;

private:
};
} // namespace CocoaTweet::API::Statuses

#endif
