using System;
using System.Collections.Generic;
using CarRentalApp.Entities;

namespace CarRentalApp.Database
{
    public static class FakeDatabase
    {
        public static List<Car> Cars = new List<Car>()
        {
            new Car
            {
                Id = Guid.NewGuid(),
                Make = "Skoda",
                Model = "Octavia",
                Year = 2003,
                Seats = 5,
                HasInsurance = false
            },
            new Car
            {
                Id = Guid.NewGuid(),
                Make = "Fiat",
                Model = "Multipla",
                Year = 2002,
                Seats = 6,
                HasInsurance = true
            }
        };

    }
}
