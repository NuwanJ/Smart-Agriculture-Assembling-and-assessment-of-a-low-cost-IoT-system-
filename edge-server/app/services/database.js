
const dbConfig = require("../config/db.config.js");

const Sequelize = require("sequelize");
const sequelize = new Sequelize(dbConfig.DB, dbConfig.USER, dbConfig.PASSWORD, {
   host: dbConfig.HOST,
   dialect: dbConfig.dialect,
   operatorsAliases: false,
   logging: false,
   pool: {
      max: dbConfig.pool.max,
      min: dbConfig.pool.min,
      acquire: dbConfig.pool.acquire,
      idle: dbConfig.pool.idle
   },
   timezone: '+05:30'
});

const db = {};

db.Sequelize = Sequelize;
db.sequelize = sequelize;

db.sensors = require("../models/sensor.model.js")(sequelize, Sequelize);
db.sensorData = require("../models/sensor.data.model.js")(sequelize, Sequelize);

db.AgriData = require("../models/data.model.js")(sequelize, Sequelize);

db.controller = require("../models/control.model.js")(sequelize, Sequelize);
db.setValues = require("../models/set.values.model.js")(sequelize, Sequelize);
db.site = require("../models/site.model.js")(sequelize, Sequelize);

db.log = require("../models/log.model.js")(sequelize, Sequelize);

module.exports = db;
