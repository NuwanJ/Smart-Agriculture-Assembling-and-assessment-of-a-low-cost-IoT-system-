
module.exports = (sequelize, Sequelize) => {
   const SensorData = sequelize.define("sensorData", {
      id: {
         type: Sequelize.INTEGER(9).UNSIGNED,
         primaryKey: true,
         autoIncrement: true
      },
      siteId: {
         type: Sequelize.INTEGER(4).UNSIGNED
      },
      x: {
         type: Sequelize.INTEGER(3).UNSIGNED
      },
      y:{
         type: Sequelize.INTEGER(3).UNSIGNED
      },
      state:{
         type: Sequelize.ENUM('ACTIVE','DEACTIVE','NULL')
      },
      firmwareVersion:{
         type: Sequelize.INTEGER(2).UNSIGNED
      },
      notes:{
         type: Sequelize.TEXT
      }
   },{
      timestamps: true,
      updatedAt: "lastUpdate",
      tableName: "sensor_data"
   });

   return SensorData;
};
