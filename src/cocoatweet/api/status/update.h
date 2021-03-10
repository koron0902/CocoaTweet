#ifndef COCOATWEET_API_STATUS_UPDATE_H_
#define COCOATWEET_API_STATUS_UPDATE_H_

#include <memory>
#include <cocoatweet/api/interface/httpPost.h>
#include <cocoatweet/api/model/tweet.h>
#include <vector>

namespace CocoaTweet::API::Statuses {
class Update : public CocoaTweet::API::Interface::HttpPost {
public:
  Update();
  void status(const std::string _status);

  void mediaId(const std::vector<std::string> _media);

  CocoaTweet::API::Model::Tweet process(std::weak_ptr<CocoaTweet::OAuth::OAuth1> _oauth);

private:
  std::string status_;
};
} // namespace CocoaTweet::API::Statuses

#endif
