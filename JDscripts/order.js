
/**
 * 判断是否是空
 * @param value
 */
function isEmpty(value){
	if(value == null || value == "" || value == "undefined" || value == undefined || value == "null"){
		return true;
	}
	else{
		value = value.replace(/\s/g,"");
		if(value == ""){
			return true;
		}
		return false;
	}
}

function useColorApi(url, type) {
  var useColorApi = $("#useColorApi").val();
  if (useColorApi == "1") {
    var t = Date.now();
    var colorHost = $("#colorHost").val();
    var colorForcebot = $("#colorForcebot").val();
    var uuid = $.cookie && $.cookie("__jda");
    var colorApiUrl = "";
    var arr = url.split('/');
    var len = arr.length;
    var url1 = arr[len - 1];
    var arr2 = url1.indexOf(".")
    var newUrl = colorHost + "?appid=trade-jd-com-v5&loginType=3&client=pc&t=" + t +
      "&clientVersion=1.0.0&uuid=" + uuid + "&functionId=pc_trade_" + url1.substring(0, arr2);
    if (colorForcebot == "1") {
      newUrl = newUrl + "&forcebot=1"
    }
    return newUrl;
  } else {
    return url;
  }
}

function getBody(str, type) {
  var useColorApi = $("#useColorApi").val();
  if (useColorApi == "1") {
    var kvMap = {};
    var kvs = str.split('&');
    for (var i = 0; i < kvs.length; i++) {
      var kvItem = kvs[i];
      var kv = kvItem.split('=');
      var k = kv[0];
      var v = kv[1];
      kvMap[k] = v;
    }
    if (type == 1) {
      return "&body=" + encodeURIComponent(JSON.stringify(kvMap));
    } else {
      return "body=" + encodeURIComponent(JSON.stringify(kvMap));
    }
  } else {
    return str;
  }
}

var actionUrl = "https://trade.jd.com/shopping/order/submitOrder.action?";
var submitOrderColorFLag = $("#submitOrderUseColorApi").val();

var param = "";
if (!isEmpty($("#sopNotPutInvoice").val())) {
  param = param + "&submitOrderParam.sopNotPutInvoice=" + $("#sopNotPutInvoice").val();
} else {
  param = param + "&submitOrderParam.sopNotPutInvoice=" + false;
}
trackID = $("#TrackID").val();
if (!isEmpty(trackID)) {
  param = param + "&submitOrderParam.trackID=" + trackID;
}
var indexFlag = param.substring(0, 1);
if (indexFlag == "&") {
  param = param.substring(1, param.length);
}
if (submitOrderColorFLag == "1") {
  actionUrl = useColorApi(actionUrl);
  var useColorFlag = $("#useColorApi").val();
  if (useColorFlag == "1") {
    actionUrl = actionUrl + "&cthr=1"
  }
  param = getBody(param);
}
var regionId = $("#regionId").val();
var shopId = $("#shopId").val();
if (regionId) {
  param += "&regionId=" + regionId;
}
if (shopId) {
  param += "&shopId=" + shopId;
}
var easyBuyFlag = $("#easyBuyFlag").val();
if (easyBuyFlag == "1" || easyBuyFlag == "2") {
  param += "&ebf=" + easyBuyFlag;
}
var ignorePriceChange = $('#ignorePriceChange').val();
if (ignorePriceChange) {
  param += "&submitOrderParam.ignorePriceChange=" + ignorePriceChange;
}
param += "&submitOrderParam.btSupport=0"; // Baitiao not supported
var eid = $('#eid').val();
if (eid) {
  param += "&submitOrderParam.eid=" + eid;
}
var fp = $('#fp').val();
if (fp) {
  param += "&submitOrderParam.fp=" + fp;
}
if ($("#flowType").val() == 15) {
  var preMainSku = $('.goods-list .goods-items .goods-item');
  if (preMainSku !== 'undefined') {
    var preMainSkuId = preMainSku[0].getAttribute('goods-id');
    if (preMainSkuId) {
      param += "&submitOrderParam.preMainSkuId=" + preMainSkuId;
    }
  }
}

var riskControl = $('#riskControl').val();
if (riskControl) {
  param += "&riskControl=" + riskControl;
}

var isBestCoupon = $('#isBestCoupon').val();
if (isBestCoupon) {
  param += "&submitOrderParam.isBestCoupon=" + isBestCoupon;
}
param += "&submitOrderParam.jxj=1"

//正品鉴定
if ($("#appraisalbuy").is(":checked")) {
  param += "&submitOrderParam.zpjd=1";
} else {
  param += "&submitOrderParam.zpjd=0";
}

//移除赠品限购
var removeGiftType = $("#giftRemoveType").val()
var limitUserFlag = $("#limitUserFlag").val()
param += "&submitOrderParam.giftRemove=" + removeGiftType;
param += "&submitOrderParam.limitUserFlag=" + limitUserFlag;

jQuery.ajax({
  type: "POST",
  dataType: "json",
  url: actionUrl,
  data: param,
  cache: false,
  xhrFields: {
    withCredentials: true //允许跨域带Cookie
  },
  success: function (result) {
    document.cookie = "__FastJD__status=0";
  },
  error: function (error) {
    document.cookie = "__FastJD__status=-1";
  }
});

document.cookie = "__FastJD__params=" + param;
document.cookie = "__FastJD__actionUrl=" + actionUrl;
document.cookie = "__FastJD__eid=" + eid;
document.cookie = "__FastJD__fp=" + fp;

