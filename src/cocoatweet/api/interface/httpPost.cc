#include <cocoatweet/api/interface/httpPost.h>
#include "cocoatweet/util/util.h"
#include <iterator>
#include <memory>
#include <vector>
#include <sstream>
#include <stdexcept>
extern "C" {
#include <curl/curl.h>
}

namespace CocoaTweet::API::Interface {
size_t HttpPost::curlCallback_(char* _ptr, size_t _size, size_t _nmemb, std::string* _stream) {
  int realsize = _size * _nmemb;
  _stream->append(_ptr, realsize);
  return realsize;
}

void HttpPost::process(std::weak_ptr<CocoaTweet::OAuth::OAuth1> _oauth,
                       std::function<void(const unsigned int, const std::string&)> _callback) {
  // エンドポイントへのパラメータにOAuthパラメータを付加して署名作成
  auto oauth       = _oauth.lock();
  auto oauthParam  = oauth->oauthParam();
  auto sigingParam = oauthParam;
  if (contentType_ == "application/x-www-form-urlencoded") {
    for (const auto [k, v] : bodyParam_) {
      sigingParam.insert_or_assign(k, v);
    }
  }

  auto signature = oauth->signature(sigingParam, "POST", url_);

  // 作成した署名をエンドポイントへのパラメータ及びOAuthパラメータに登録
  oauthParam.merge(signature);

  // リクエストボディの構築
  std::string requestBody = "";
  {
    std::vector<std::string> tmp;
    for (const auto& [key, value] : bodyParam_) {
      tmp.push_back(key + "=" + value);
    }
    requestBody = CocoaTweet::Util::join(tmp, "&");
  }

  // ヘッダの構築
  std::string oauthHeader = "authorization: OAuth ";
  {
    std::vector<std::string> tmp;
    for (const auto& [key, value] : oauthParam) {
      tmp.push_back(key + "=" + CocoaTweet::Util::urlEncode(value));
    }
    oauthHeader += CocoaTweet::Util::join(tmp, ",");
  }

  // do post
  CURL* curl;
  CURLcode res;
  std::string rcv;
  long responseCode;
  curl = curl_easy_init();
  url_ = url_;
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestBody.length());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallback_);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (std::string*)&rcv);
#ifndef NDEBUG
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
    // Headerを保持するcurl_slist*を初期化
    struct curl_slist* headers = NULL;
    // Authorizationをヘッダに追加
    headers = curl_slist_append(headers, oauthHeader.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    res = curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
    curl_easy_cleanup(curl);
  }

  if (res != CURLE_OK) {
    throw std::runtime_error(std::string("INTERNAL ERROR : curl(") + std::to_string(res) + ")");
    exit(1);
  }

  if (_callback) {
    _callback(responseCode, rcv);
  }
}
} // namespace CocoaTweet::API::Interface
