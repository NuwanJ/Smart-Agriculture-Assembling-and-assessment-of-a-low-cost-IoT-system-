
module.exports = (sequelize, Sequelize) => {
   const AgriData = sequelize.define("agriData", {
      id: {
         type: Sequelize.INTEGER.UNSIGNED,
         primaryKey: true,
         autoIncrement: true
      },
      dKey: {
         type: Sequelize.TEXT
      },
      dValue: {
         type: Sequelize.TEXT
      }
   },{
      timestamps: false,
      updatedAt: false,
      tableName: "agri_data"
   });

   return AgriData;
};
