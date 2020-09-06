// #include <boost/asio.hpp>
#include <aws/core/Aws.h>
#include <aws/translate/TranslateClient.h>
#include <aws/translate/model/TranslateTextRequest.h>
#include <iostream>
int main(int argc, char *argv[]) {
  Aws::SDKOptions options;
  Aws::InitAPI(options);

  // use the sdk
  auto translate_text_request = Aws::Translate::Model::TranslateTextRequest();
  translate_text_request.WithText("My name is John").WithSourceLanguageCode("en").WithTargetLanguageCode("es");
  auto translate_client = Aws::Translate::TranslateClient();
  auto translate_outcome = translate_client.TranslateText(translate_text_request);
  auto translate_results = translate_outcome.GetResult();

  std::cout << translate_results.GetTranslatedText().c_str() << std::endl;
  Aws::ShutdownAPI(options);
  return 0;
}