#ifndef URLS_H
#define URLS_H

#include <QUrl>

namespace JD {

static const char loginUrl[]    = "https://passport.jd.com/new/login.aspx";
static const char statusUrl[]   = "https://qr.m.jd.com/check?callback=jQuery%1&appid=133&token=%2&_=%3";
static const char ticketUrl[]   = "https://passport.jd.com/uc/qrCodeTicketValidation?t=%1";
static const char mainUrl[]     = "https://www.jd.com/";
static const char homeUrl[]     = "https://home.jd.com/";
static const char searchUrl[]   = "https://search.jd.com/Search?keyword=%1&enc=utf-8";
static const char itemUrl[]     = "https://item.jd.com/%1.html";
static const char qrCodeSrc[]   = "https://qr.m.jd.com/show?appid=133&size=147&t=%1&sa=1";
static const char addItemUrl[]  = "https://cart.jd.com/gate.action?pid=%1&pcount=%2&ptype=1";
static const char checkoutUrl[] = "https://trade.jd.com/shopping/order/getOrderInfo.action";
static const char error2Url[]   = "https://www.jd.com/error2.aspx";
static const char error104Url[] = "https://trade.jd.com/shopping/orderBack.html";
static const auto domainCompareRules = QUrl::RemoveFilename | QUrl::NormalizePathSegments | QUrl::RemoveQuery;
static const auto fileCompareRules = QUrl::NormalizePathSegments | QUrl::RemoveQuery;
static const char orderScriptHeader[] = R"(
// ==UserScript==
// @name my_submit_order
// @include https://trade.jd.com/shopping/order/getOrderInfo.action
// @run-at document-end
// ==/UserScript==
)";

static const char itemNameSelector[] = R"(
document.querySelector("div.w div.itemInfo-wrap div.sku-name").textContent;
)";

static const char itemPriceSelector[] = R"(
document.querySelector("div.w div.itemInfo-wrap div.summary-price-wrap span.p-price").textContent;
)";

static const char itemStockSelector[] = R"(
document.getElementById("store-prompt").textContent;
)";

static const char shopNameSelector[] = R"(
document.querySelector("div.crumb-wrap div.item div.name").textContent;
)";

static const char submitUrl[] = "https://api.m.jd.com/api?appid=trade-jd-com-v5&loginType=3&client=pc&t=%1&clientVersion=1.0.0&uuid=%2&functionId=pc_trade_submitOrder&cthr=1";

static const char submitPayload1[] = "body=%7B%22submitOrderParam.sopNotPutInvoice%22%3A%22false%22%2C%22submitOrderParam.trackID%22%3A%22TestTrackId%22%7D&submitOrderParam.ignorePriceChange=0&submitOrderParam.btSupport=0";
static const char submitPayload2[] =
"&submitOrderParam.eid=%1&submitOrderParam.fp=%2&submitOrderParam.jxj=1&submitOrderParam.zpjd=1&submitOrderParam.giftRemove=0&submitOrderParam.limitUserFlag=67776";

} // namespace JD

#endif // URLS_H
