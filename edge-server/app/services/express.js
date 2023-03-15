'use strict'

const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const app = express();

const apiControl = require("../routes/control.routes.js");
const apiSensor = require("../routes/sensor.routes.js");
const apiSetValues = require("../routes/set.values.routes.js");
const apiSite = require("../routes/site.routes.js");
const apiLogs = require("../routes/log.routes.js");


//"http://localhost:8000"
app.use(cors({origin: "*"}));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get("/", (req, res) => {
   res.json({ message: "Welcome to GreenHouse Backend" });
});

app.use('/v1/controllers', apiControl);
app.use('/v1/sensors', apiSensor);
app.use('/v1/setvalues', apiSetValues);
app.use('/v1/sites', apiSite);
app.use('/v1/logs', apiLogs);

exports.start = () => {
   const PORT = process.env.PORT || 8080;

   app.listen(PORT, () => {
      console.log(`Server is running on port ${PORT}.`);
   });
}

exports.app = app;
