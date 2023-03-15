require('dotenv').config()

const axios = require('axios');

const db = require("./services/database.js");
const app = require("./services/express")
const mqtt = require("./services/mqtt.js");
const cron = require("./services/cron.js");

app.start()
mqtt.start();

cron.begin(mqtt, db);

// force:true to drop the table if it already exists
db.sequelize.sync({ force: false }).then(() => {
   console.log("sequalize: started");
});


/*

ProxyPass /api/v1 http://localhost:8080/v1
ProxyPassReverse /api/v1 http://localhost:8080/v1


ProxyPass /web/v1 http://10.40.2.72:80/dashboard
ProxyPassReverse /web/v1 http://10.40.2.72:80/dashboard

*/
