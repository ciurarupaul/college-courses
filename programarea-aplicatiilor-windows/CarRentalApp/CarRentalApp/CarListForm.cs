using System.Windows.Forms;
using CarRentalApp.Database;

namespace CarRentalApp
{
    public partial class CarListForm: Form
    {
        public CarListForm()
        {
            // trece prin designer 
            InitializeComponent();

            // trebuie sa fie inainte de set datasrc, daca il vrei
            //carsDataGridView.AutoGenerateColumns = true;

            carsDataGridView.AutoGenerateColumns = false;
            carsDataGridView.DataSource = FakeDatabase.Cars;

            AddTextBoxColumn("Id", "ID", isVisible: false);
            AddTextBoxColumn("Make", "Marca");
            AddTextBoxColumn("Model", "Model");
            AddTextBoxColumn("Year", "An fabricatie", 70);
            AddCheckBoxColumn("HasInsurance", "Are asigurare", 50);
        }

        private void AddTextBoxColumn(string propertyName, string headerText, int width = 100, bool isVisible = true)
        {
            // parametrii optionali TREBUIE pusi la finalul listei de params !!!
            var column = new DataGridViewTextBoxColumn();
            column.DataPropertyName = propertyName;
            column.Name = propertyName;
            column.HeaderText = headerText;
            column.Width = width;   // width e optional, are default value
            column.Visible = isVisible;
            carsDataGridView.Columns.Add(column);
        }

        private void AddCheckBoxColumn(string propertyName, string headerText, int width = 100, bool isVisible = true)
        {
            var column = new DataGridViewCheckBoxColumn();
            column.DataPropertyName = propertyName;
            column.Name = propertyName;
            column.HeaderText = headerText;
            column.Width = width;
            column.Visible = isVisible;
            carsDataGridView.Columns.Add(column);
        }
    }
}
