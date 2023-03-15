
module.exports = (sequelize, Sequelize) => {
   const SetValues = sequelize.define("setvalues", {
      siteId: {
         type: Sequelize.INTEGER(5).UNSIGNED,
         primaryKey: true,
      },
      temp: {
         type: Sequelize.FLOAT
      },
      humidity:{
         type: Sequelize.FLOAT
      },
      light:{
         type: Sequelize.FLOAT
      },
      version:{
         type: Sequelize.INTEGER(2).UNSIGNED
      }
   },{
      timestamps: true,
      updatedAt: "lastUpdate",
      tableName: "set_values"
   });

   return SetValues;
};
