using System;

namespace CarRentalApp.Entities
{
    public class Car
    {
        public Guid Id { get; set; }
        public string Make { get; set; }
        public string Model { get; set; }
        public int Year { get; set; }
        public int Seats { get; set; }
        public bool HasInsurance { get; set; }
    }
}
