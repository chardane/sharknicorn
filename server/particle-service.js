// make API call to Particle server to invoke our "state-change" Particle function
exports.stateChange = function (ride_status) {

  const https = require('https');
  const querystring = require('querystring');
  const device_url = "https://api.particle.io/v1/devices/" + process.env.DEVICE_UUID + "/state-change";

  console.log("requesting change: ", ride_status);

  var postData = querystring.stringify({
    args: ride_status,
    access_token: process.env.DEVICE_ACCESS_TOKEN
  });


  const options = {
    hostname: 'api.particle.io',
    path: device_url,
    method: 'POST',
    headers: {
      'Content-Type': 'application/x-www-form-urlencoded',
      'Content-Length': postData.length
    }
  };

  const req = https.request(options, (res) => {
    console.log('statusCode:', res.statusCode);
    var result = '';

    res.on('data', (chunk) => {
      result += chunk;
    });

    res.on('end', () => {
      console.log(result);
    });
  });

  // write data to request body
  req.write(postData);
  req.end();
}
