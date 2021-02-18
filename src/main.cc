#include "cocoatweet/oauth/key.h"
#include "cocoatweet/api/api.h"

auto main() -> int {
  // Generate Key object
  // auto consumerKey           = "your consumer key";
  // auto consumerSecret        = "your consumer secret";
  // auto accessToken           = "your access token";
  // auto accessTokenSecret     = "your access token secret";
  // CocoaTweet::OAuth::Key key = CocoaTweet::OAuth::Key(consumerKey,
  //                                                     consumerSecret,
  //                                                     accessToken,
  //                                                     accessTokenSecret);

  // also can generate Key object from JSON file
  // CocoaTweet::OAuth::Key key = CocoaTweet::OAuth::Key::fromJsonFile("api_key.json");

  // Generate API Entry object using Key object
  // CocoaTweet::API::API api(key);

  // Now, you can use a twitter api
  // api.status().Update("Hello Twitter World from Cocoa Twitter Library");
  // api.favorite().Create("tweet id you want to fav.");
  // api.favorite().Destroy("tweet id you want to un_fav.");
}
