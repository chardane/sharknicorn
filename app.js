const express = require('express')
const app = express()
const particleService = require("./particle-service")

// access variables from .env file
require('dotenv').config()

// populate req.body in json
var bodyParser = require('body-parser');
// use a raw parser, so that we can validate webhook correctly
app.use(bodyParser.raw({type: 'application/json'}))

app.post('/webhook', function (req, res) {

  var req_body = JSON.parse(req.body.toString());
  // only do things when event: all_trips.status_changed
  // because sandbox gives you double webhooks
  if (validateWebhook(req) && (req_body.event_type == "all_trips.status_changed")){
    var rideStatus = req_body.meta.status;
    particleService.stateChange(rideStatus);
  }

  //respond to the webhook server with a 200 right away
  res.status(200).send('Received!');
});

function validateWebhook(req){
  const crypto = require('crypto');
  const hmac = crypto.createHmac('sha256', process.env.uber_client_secret);

  // make sure that we used bodyParser.raw() for req
  // so that we're computing based on the raw request, not the parsed one
  var computed = hmac.update(req.body).digest('hex');
  var signature = req.headers['x-uber-signature'];

  return computed == signature ? true : false;
}

app.listen(3000, () => console.log('Sharknicorn listening on port 3000!'));
