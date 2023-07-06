#ifndef URLS_H
#define URLS_H

#include <QUrl>

namespace JD {

static const char loginUrl[]    = "https://passport.jd.com/new/login.aspx";
static const char mainUrl[]     = "https://www.jd.com/";
static const char homeUrl[]     = "https://home.jd.com/";
static const char itemUrl[]     = "https://item.jd.com/%1.html";
static const char qrCodeSrc[]   = "https://qr.m.jd.com/show?appid=133&size=147&t=%1&sa=1";
static const char addItemUrl[]  = "https://cart.jd.com/gate.action?pid=%1&pcount=%2&ptype=1";
static const char checkoutUrl[] = "https://trade.jd.com/shopping/order/getOrderInfo.action";
static const char error2Url[]   = "https://www.jd.com/error2.aspx";
static const char error104Url[] = "https://trade.jd.com/shopping/orderBack.html";
static const auto urlCompareRules = QUrl::RemoveFilename | QUrl::NormalizePathSegments | QUrl::RemoveQuery;
static const auto errorCheckRules = QUrl::NormalizePathSegments | QUrl::RemoveQuery;
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

} // namespace JD

#endif // URLS_H
