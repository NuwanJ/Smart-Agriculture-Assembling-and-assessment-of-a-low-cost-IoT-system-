module.exports = {
  HOST: "localhost",
  USER: "iot-user",
  PASSWORD: "iotqLhS3BHBsql",
  DB: "agri_iot",
  dialect: "mysql",
  pool: {
    max: 5,
    min: 0,
    acquire: 30000,
    idle: 10000
  }
};
