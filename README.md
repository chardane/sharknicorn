# Sharknicorn Hat
This repo contains the sample code for making an Uber-aware hat that I describe in [this article](https://medium.com/@charlyn/12-months-of-makes-88bc288d41df).

# Installation

After cloning this repo:
```
cd server/
npm install
```

# Firmware

Copy the contents of `firmware/sharknicorn.ino` to a new app in your Particle dashboard [build.particle.io](https://build.particle.io).

You must setup your Particle device using `particle.io/start` or [watch this video that uses the Particle mobile app to setup](https://vimeo.com/178282058)

# Server Setup

1. You must have ngrok installed
2. You must have nodeJS installed

## Gather credentials
Then, create a file `.env` inside your `server/` folder (make sure it's inside the server folder!)
```
touch .env
```
and put this in the file:
```
UBER_CLIENT_SECRET=YOUR_UBER_CLIENT_SECRET
DEVICE_UUID=YOUR_PARTICLE_DEVICE_UUID
DEVICE_ACCESS_TOKEN=YOUR_PARTICLE_DEVICE_ACCESS_TOKEN
```
The following describes how you can get the above values:
1. Go to [developer.uber.com](http://developer.uber.com/), click `Sign in` and log into the developer dashboard with your existing Uber account. If you do not have an Uber account you will have to sign up for one.
    - Then, when you get access to the developer dashboard, click "create app"
    - Copy your `Client Secret` and replace `YOUR_UBER_CLIENT_SECRET` above with it
2. Go to [build.particle.io](https://build.particle.io/)
    - Click on the Devices icon (looks like a scope)
      - Click on the `>` arrow next to your device
      - Copy your `Device ID` and replace `YOUR_PARTICLE_DEVICE_UUID` above with it
    - Click on the Settings icon (looks like a gear)
      - Copy your `Access Token`, and replace `YOUR_PARTICLE_DEVICE_ACCESS_TOKEN` above with it




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
Make sure you click `Save` at the bottom of the page! Note that this ngrok URL changes everytime you quit ngrok.

That's it! Your server is now running and is now connected to your Particle Device

# Testing

Go back to your developer dashboard, and while inside your app's settings page, click on `Trip Simulator` (on the bottom of the left side bar)

Start a trip and watch your webhooks hit your local server!

Your Sharknicorn should be lighting up in different animations as well.
