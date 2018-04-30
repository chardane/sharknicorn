const http = require('http');


var postData = JSON.stringify({
  workflow_id: "4c215418-8a3b-44e7-82f6-1c63edb01e6a",
});


const options = {
  hostname: 'dc4eb60f.ngrok.io',
  path: "/orders/estimate",
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
    'Content-Length': postData.length
  }
};

const req = http.request(options, (res) => {
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
