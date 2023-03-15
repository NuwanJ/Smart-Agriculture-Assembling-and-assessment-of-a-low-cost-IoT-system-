
module.exports = (sequelize, Sequelize) => {
   const Sensor = sequelize.define("sensor", {
      id: {
         type: Sequelize.INTEGER.UNSIGNED,
         primaryKey: true,
         autoIncrement: true
      },
      sensorId: {
         type: Sequelize.INTEGER(5).UNSIGNED
      },
      seqNo: {
         type: Sequelize.INTEGER(4).UNSIGNED
      },
      temp1: {
         type: Sequelize.FLOAT
      },
      temp2: {
         type: Sequelize.FLOAT
      },
      temp3: {
         type: Sequelize.FLOAT
      },
      humidity1:{
         type: Sequelize.FLOAT
      },
      humidity2:{
         type: Sequelize.FLOAT
      },
      humidity3:{
         type: Sequelize.FLOAT
      },
      light:{
         type: Sequelize.FLOAT
      },
      soilMoisture:{
         type: Sequelize.FLOAT
      },
      version:{
         type: Sequelize.INTEGER(2).UNSIGNED
      }
   },{
      timestamps: true,
      updatedAt: false,
      tableName: "sensor_log"
   });

   return Sensor;
};
