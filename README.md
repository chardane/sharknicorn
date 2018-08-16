# Sharknicorn Hat
This repo contains the sample code for making an Uber-aware hat that I describe in [this article](https://medium.com/@charlyn/12-months-of-makes-88bc288d41df).

# Prerequisites

1. You must have ngrok installed
2. You must have nodeJS installed
3. You must setup your Particle device using `particle.io/start` or [watch this video that uses the Particle mobile app to setup](https://vimeo.com/178282058)
3. Go to [developer.uber.com](http://developer.uber.com/), click `Sign in` and log into the developer dashboard with your existing Uber account. If you do not have an Uber account you will have to sign up for one.
  - Then, when you get access to the developer dashboard, click "create app"
  - find your `Client Secret` and take note of it, you'll need it below.
4. Go to [build.particle.io](https://build.particle.io/)
  - Click on the Devices icon (looks like a scope)
    - Click on the `>` arrow next to your device
    - Take note of the `Device ID`, you'll need it below
  - Click on the Settings icon (looks like a gear)
    - Take note of the `Access Token`, you'll need it below

# Server Setup

1. After cloning this repo, `cd` into `server/` and run
```
npm install
```
2. Then, create a file `.env` inside your `server/` folder (make sure it's inside the server folder!)
```
touch .env
```
and put this in the file:
```
UBER_CLIENT_SECRET=YOUR_UBER_CLIENT_SECRET
DEVICE_UUID=YOUR_PARTICLE_DEVICE_UUID
DEVICE_ACCESS_TOKEN=YOUR_PARTICLE_DEVICE_ACCESS_TOKEN
```

# Running the server

While still in the `server` folder, run
```
node app.js
```
This will serve in port `3000`

In another terminal, run `ngrok`
```
ngrok http 3000
```

Copy paste the `https` version of the `Forwarding` URL to the `Webhook URL` in the "Settings" tab of your [Uber developer dashboard](https://developer.uber.com/dashboard), appended with `/webhook`

For example:
```
https://55fe6bd8.ngrok.io/webhook
```
Make sure you click `Save` at the bottom of the page!

That's it! Your server is now running and is now connected to your Particle Device

# Testing

Go back to your developer dashboard, and while inside your app's settings page, click on `Trip Simulator` (on the bottom of the left side bar)

Start a trip and watch your webhooks hit your local server!

Your Sharknicorn should be lighting up in different animations as well.
