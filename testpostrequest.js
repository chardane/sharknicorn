var request = require('request')

var postData = {
	"workflow_id": "03d64c13-330b-4533-9ebd-5646380095fc"
}

var url = 'http://dc4eb60f.ngrok.io/orders/estimate'
var options = {
  method: 'post',
  body: postData,
  json: true,
  url: url
}
request(options, function (err, res, body) {
  if (err) {
    console.error('error posting json: ', err)
    throw err
  }
  var headers = res.headers
  var statusCode = res.statusCode
  console.log('options: ', options)
  console.log('headers: ', headers)
  console.log('statusCode: ', statusCode)
  console.log('body: ', body)
})
